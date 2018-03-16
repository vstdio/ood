#pragma once
#include <string>
#include <cassert>

// ����� ����������� � ������� ������ ��� ����� � ��������.
//  ������ enum'� ����� ���� �� ������� ���������.
enum class CoffeePortionSize
{
	Standard,
	Double
};

// ����� ���� �� ������ ���������
enum class MilkshakePortionSize
{
	Small,
	Medium,
	Large
};

std::string ToString(MilkshakePortionSize portionSize);
std::string ToString(CoffeePortionSize portionSize);
