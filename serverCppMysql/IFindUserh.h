#pragma once
class IFindUser {
public:
	virtual ~IFindUser() = default;
	virtual std::string searchUser() = 0;
}