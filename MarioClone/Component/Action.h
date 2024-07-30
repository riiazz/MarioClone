#pragma once
#include <iostream>

class Action
{
	std::string m_name;
	std::string m_type;

public:
	Action() = default;
	const std::string& name() const;
	const std::string& type() const;
};

