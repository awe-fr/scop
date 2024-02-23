#include "../headers/major.h"

GLuint	loadDDS(const char *imagepath) {
	unsigned char	header[124];
	FILE *fp;

	// open the file
	fp = fopen(imagepath, "rb");
	if (fp == NULL)
		return (0);

	// check if DDS
	char	filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ",4) != 0) {
		fclose(fp);
		return (0);
	}

	// get header and assign
	fread(&header, 124, 1, fp);
	unsigned int	height = *(unsigned int *)&(header[8]);
	unsigned int	width = *(unsigned int *)&(header[12]);
	unsigned int	linearSize = *(unsigned int *)&(header[16]);
	unsigned int	mipMapCount = *(unsigned int *)&(header[24]);
	unsigned int	fourCC = *(unsigned int *)&(header[80]);

	// get mipMap
	unsigned char	*buffer;
	unsigned int	bufsize;

	if (mipMapCount > 1)
		bufsize = linearSize * 2;
	else
		bufsize = linearSize;
	buffer = (unsigned char *)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	// convert indicator for opengl
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

GLuint	loadBMP_custom(const char * imagepath) {
	unsigned char   header[54]; //every BMP file begin by a header (size 54)
	unsigned int    dataPos;    //pose where data begin
	unsigned int    width;
	unsigned int    height;
	unsigned int    imageSize;  // = width * height * 3
	unsigned char   *data;

	FILE    *file = fopen(imagepath, "rb");
	if (!file) {
		std::cout << "Image could not be opened" << std::endl;
		return (1); 
	}
	if (fread(header, 1, 54, file) != 54) {
		std::cout << "Not a correct BMP file" << std::endl;
		return (1);
	}
	if (header[0] != 'B' || header[1] != 'M') {
		std::cout << "Not a correct BMP file" << std::endl;
		return (1);
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char [imageSize];
	
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	return (0);
}

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

GLuint	loadTGA(const char *imagepath) {
	GLuint  textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int nrChannels;
	int width;
	int height;
	unsigned char   *data = stbi_load(imagepath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum  format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);

	return (textureID);
}