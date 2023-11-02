#pragma once
#include <iostream>

template <class HashDataType>
struct Widget
{
	HashDataType m_width;
	HashDataType m_height;

	bool operator==(const Widget& other) const
	{
		return (m_width == other.m_width && m_height == other.m_height);
	}
	bool operator!=(const Widget& other) const
	{
		return (m_width != other.m_width || m_height != other.m_height);
	}
	friend std::ostream& operator<<(std::ostream& os, const Widget& widget)
	{
		os << widget.m_width << ' ' << widget.m_height;
		return os;
	}


};
