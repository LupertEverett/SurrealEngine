#pragma once

enum class ImageFormat
{
	R8G8B8A8
};

class Image
{
public:
	virtual ~Image() = default;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual ImageFormat GetFormat() const = 0;
	virtual void* GetData() const = 0;

	static std::shared_ptr<Image> Create(int width, int height, ImageFormat format, const void* data);
};
