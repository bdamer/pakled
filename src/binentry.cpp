#include "stdafx.h"
#include "binentry.h"

using namespace dukat;

namespace pakled
{
	bool compare(const AABB2& a, const AABB2& b)
	{
		const auto dw = a.width() - b.width();
		if (dw == 0.0f)
			return (a.height() - b.height()) <= 0.0f;
		else
			return dw <= 0.0f;
	}
	
	bool compare(const dukat::Rect& a, const dukat::Rect& b)
	{
		const auto delta = a.w - b.w;
		if (delta == 0)
			return (a.h - b.h) <= 0;
		else
			return delta <= 0;
	}
}