#pragma once

namespace pakled
{
	bool compare(const dukat::AABB2& a, const dukat::AABB2& b);
	bool compare(const dukat::Rect& a, const dukat::Rect& b);

	struct ImageEntry
	{
		std::string filename;
		std::unique_ptr<dukat::Surface> surface;
	
		ImageEntry(void) : filename(""), surface(nullptr) { }
	};

	struct BinEntry
	{
		dukat::Rect rect;
		ImageEntry* img;

		bool operator< (const BinEntry& other) const { return compare(rect, other.rect); }
		bool operator> (const BinEntry& other) const { return !compare(rect, other.rect); }
	};
}