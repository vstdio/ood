#include "stdafx.h"
#include "../Observer.h"
#include <boost/test/output_test_stream.hpp>

namespace
{
class DummyObservable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	virtual int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DummyObserver : public IObserver<int>
{
public:
	DummyObserver(DummyObservable& observable, const std::string& name,
		bool eraseOnUpdate,
		boost::test_tools::output_test_stream& output)
		: m_observable(observable)
		, m_name(name)
		, m_eraseOnUpdate(eraseOnUpdate)
		, m_output(output)
	{
		m_observable.RegisterObserver(*this);
	}

	~DummyObserver()
	{
		// �� ������ ������� ������� ���������
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		m_output << m_name;
		if (m_eraseOnUpdate)
		{
			// �� ������ ������� ������� ���������
			m_observable.RemoveObserver(*this);
		}
	}

	void SetEraseOnUpdate(bool eraseOnUpdate)
	{
		m_eraseOnUpdate = eraseOnUpdate;
	}

private:
	DummyObservable& m_observable;
	boost::test_tools::output_test_stream& m_output;
	std::string m_name;
	bool m_eraseOnUpdate;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStation)
	BOOST_AUTO_TEST_CASE(subsribers_can_remove_themselves_from_list_safely)
	{
		boost::test_tools::output_test_stream output;

		DummyObservable observable;
		DummyObserver observer1(observable, "a", true, output);
		DummyObserver observer2(observable, "b", false, output);

		observable.SetData(123);
		// �� �������� ��� ������� ������ ������������ ����� �� ������������
		BOOST_CHECK(output.is_equal("ab") || output.is_equal("ba"));

		output.clear();
		observer2.SetEraseOnUpdate(true);
		observable.SetData(456);
		// ����������� � ������ "a" ������ ���� �� ����������� � ������� �����������
		BOOST_CHECK(output.is_equal("b"));

		output.clear();
		// ����������� � ������ "b" ������ ���� �� ����������� � ������� �����������
		observable.SetData(789);
		BOOST_CHECK(output.is_empty());
	}
BOOST_AUTO_TEST_SUITE_END()
