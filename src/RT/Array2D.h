#pragma once

#include "Math.h"
#include <memory>

namespace RT
{
	template<class Elem>
	class Array2D
	{
	public:
		struct Coords {
			int x, y;
		};

		// создает пустой массив нулевого размера
		Array2D() = default;

		// создает массив заданного размера с неинициализированными значениями
		explicit Array2D(const Rect& rect_)
			: rect(rect_)
		{
			const int size = rect.width * rect.height;
			if (rect.width * rect.height > 0) {
				data.reset(new Elem[size]);
			} else {
				rect.width = rect.height = 0;
			}
		}

		template<class T>
		Array2D(const Rect& rect_, const T& value)
			: Array2D(rect_)
		{
			std::fill(begin(), end(), value);
		}

		Array2D(const Array2D& other)
			: Array2D(other.rect)
		{
			std::copy(other.begin(), other.end(), begin());
		}

		Array2D(Array2D&& other) noexcept
			: rect(other.rect)
			, data(std::move(other.data))
		{}

		Array2D& operator=(const Array2D& other)
		{
			rect = other.rect;
			if (rect.width * rect.height > 0) {
				data.reset(new Elem[static_cast<size_t>(rect.width * rect.height)]);
				std::copy(other.begin(), other.end(), begin());
			} else {
				data.reset();
			}
			return *this;
		}

		Array2D& operator=(Array2D&& other) noexcept
		{
			rect = other.rect;
			data = std::move(other.data);
			return *this;
		}

		const Rect& GetRect() const {
			return rect;
		}

		Elem& operator[](const Coords& pt) {
			return data[rect.width * (pt.y - rect.y) + (pt.x - rect.x)];
		}

		const Elem& operator[](const Coords& pt) const {
			return data[rect.width * (pt.y - rect.y) + (pt.x - rect.x)];
		}

		Elem* begin() { return data.get(); }
		Elem* end() { return data.get() + rect.width * rect.height; }
		const Elem* begin() const { return data.get(); }
		const Elem* end() const { return data.get() + rect.width * rect.height; }

	private:
		std::unique_ptr<Elem[]> data;
		Rect rect;
	};


	template<class Elem>
	void CopyArray2DData(const Array2D<Elem>& src, Array2D<Elem>& dst) {
		const auto src_rect = src.GetRect();
		for (int y = src_rect.y; y < src_rect.y + src_rect.height; ++y) {
			for (int x = src_rect.x; x < src_rect.x + src_rect.width; ++x) {
				dst[{x, y}] = src[{x, y}];
			}
		}
	}
}