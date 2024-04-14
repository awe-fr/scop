#include "../headers/major.hpp"

GLuint	loadDDS(const char *imagepath) {
	unsigned char	header[124];
	FILE *fp;

	fp = fopen(imagepath, "rb");
	if (fp == NULL)
		return (0);

	//parsing
	char	filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ",4) != 0) {
		fclose(fp);
		return (0);
	}

	fread(&header, 124, 1, fp);
	unsigned int	height = *(unsigned int *)&(header[8]);
	unsigned int	width = *(unsigned int *)&(header[12]);
	unsigned int	linearSize = *(unsigned int *)&(header[16]);
	unsigned int	mipMapCount = *(unsigned int *)&(header[24]);
	unsigned int	fourCC = *(unsigned int *)&(header[80]);

	unsigned char	*buffer;
	unsigned int	bufsize;

	if (mipMapCount > 1)
		bufsize = linearSize * 2;
	else
		bufsize = linearSize;
	buffer = (unsigned char *)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int	components;
	unsigned int	format;

	if (fourCC == FOURCC_DXT1)
		components = 3;
	else
		components = 4;

	if (fourCC == FOURCC_DXT1)
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	else if (fourCC == FOURCC_DXT3)
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	else if (fourCC == FOURCC_DXT5)
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	else {
		free(buffer);
		return (0);
	}

	// texture creation
	GLuint	textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	

	unsigned int	blockSize;
	unsigned int	offset = 0;

	if (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) 
		blockSize = 8;
	else
		blockSize = 16;

	for (unsigned int level = 0; level <  mipMapCount && (width || height); ++level) {
		unsigned int	size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer);
	return textureID;
}