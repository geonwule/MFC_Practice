#pragma once
class Observer : public CSocket
{
public:
	virtual void update(int id, CString strPrice) = 0;

	virtual int getID() const = 0;
	virtual ~Observer() = default;
};

