#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <algorithm>

const double eps = -1e-8;

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {}

	void update(double next) override {
		if (m_min - next >= eps) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics
{
public:
	Max() : m_max(std::numeric_limits<double>::min()) {}

	void update(double next) override
	{
		if (next - m_max >= eps)
		{
			m_max = next;
		}
	}

	double eval() const override
	{
		return m_max;
	}

	const char* name() const override
	{
		return "max";
	}
private:
	double m_max;
};

class Mean : public IStatistics
{
public:
	Mean() : m_mean(0) {sum = 0; count = 0;}

	void update(double next) override
	{
		sum += next;
		count++;

		m_mean = sum / count;
	}

	double eval() const override
	{
		return m_mean;
	}

	const char* name() const override
	{
		return "mean";
	}
private:
	double m_mean;
	double sum;
	int count;
};

class Std : public IStatistics
{
public:
	Std() : m_std(0), m_mean() {}

	void update(double next) override
	{
		elements.push_back(next);
		m_mean.update(next);
		double sum = 0;
		for (double x : elements)
		{
			sum += std::pow(x - m_mean.eval(), 2);
		}

		double dispersion = sum / elements.size();
		m_std = std::sqrt(dispersion);
	}

	double eval() const override
	{
		return m_std;
	}

	const char* name() const override
	{
		return "std";
	}
private:
	double m_std;
	std::vector<double> elements;
	Mean m_mean;
};

class Pct90 : public IStatistics
{
public:
	Pct90() : m_pct90(0), count(0) {}

	void update(double next) override
	{
		v.push_back(next);
		std::sort(v.begin(), v.end());

		int index = std::floor((v.size() - 1) * 0.9 + (double)1 + (double)0.5);

		m_pct90 = v[index - 1];
	}

	double eval() const override
	{
		return m_pct90;
	}

	const char* name() const override
	{
		return "pct90";
	}
private:
	double m_pct90;
	int count = 0;
	std::vector<double> v;
};

class Pct95 : public IStatistics
{
public:
	Pct95() : m_pct95(0) {}

	void update(double next) override
	{
		v.push_back(next);
		std::sort(v.begin(), v.end());

		int index = std::floor((v.size() - 1) * 0.95 + (double)1 + (double)0.5);

		m_pct95 = v[index - 1];
	}

	double eval() const override
	{
		return m_pct95;
	}

	const char* name() const override
	{
		return "pct95";	
	}
private:	
	double m_pct95;
	std::vector<double> v;
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}
	std::cout << "\n";
	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}