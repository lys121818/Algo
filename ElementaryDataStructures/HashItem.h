#pragma once

template<typename DataType>
class HashItem
{
public:
	HashItem()
		:m_key(-1)
	{

	}

	~HashItem()
	{

	}

	int GetKey() { return m_key; }
	void SetKey(int k) { m_key = k; }

	DataType GetObject() { return m_object; }
	void SetObject(DataType obj) { m_object = obj; }

	bool operator==(HashItem& item)
	{
		if (m_key == item.GetKey())
			return true;
		return false;
	}
	void operator=(HashItem& item)
	{
		m_key = item.GetKey();
		m_object = item.GetObject();
	}

private:
	int m_key;
	DataType m_object;
};