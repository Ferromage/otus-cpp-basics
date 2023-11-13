#include <iostream>
#include <limits>
#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>

#define LENGTH_OF(x) sizeof(x) / sizeof(x[0])

namespace {
	double calculateAvg(const std::vector<double>& data) {
		double result = 0.0;
		for (double num : data) {
			result += num / data.size();
		}
		return result;
	}
}

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};


class Min : public IStatistics {
public:
	Min() {}

	void update(double next) override {
		if (!m_min || next < m_min.value()) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min.value_or(std::numeric_limits<double>::min());
	}

	const char * name() const override {
		return "min";
	}

private:
	std::optional<double> m_min;
};


class Max : public IStatistics {
public:
	Max() {}

	void update(double next) override {
		if (!m_max || next > m_max.value()) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max.value_or(std::numeric_limits<double>::max());
	}

	const char * name() const override {
		return "max";
	}

private:
	std::optional<double> m_max;
};


class Mean : public IStatistics {
public:
	Mean() {}

	void update(double next) override {
		m_array.push_back(next);
		m_cache.reset();
	}

	double eval() const override {
		if (!m_cache) {
			m_cache = calculateAvg(m_array);
		}
		return m_cache.value();
	}

	const char * name() const override {
		return "mean";
	}

private:
	std::vector<double> m_array;
	mutable std::optional<double> m_cache;
};


class Std : public IStatistics {
public:
	Std() {}

	void update(double next) override {
		m_array.push_back(next);
		m_cache.reset();
	}

	double eval() const override {
		if (!m_cache) {
			const auto avg = calculateAvg(m_array);

			double sum = 0.0;
			for (double num : m_array) {
				sum += (std::pow((num -  avg), 2)) / m_array.size();
			}

			m_cache = std::sqrt(sum);
		}

		return m_cache.value();
	}

	const char * name() const override {
		return "std";
	}

private:
	std::vector<double> m_array;
	mutable std::optional<double> m_cache;
};


class Pct90 : public IStatistics {
public:
	Pct90() {}

	void update(double next) override {
		m_array.push_back(next);
		m_cache.reset();
	}

	double eval() const override {
		if (m_array.empty()) {
			return 0.0;
		}

		if (!m_cache) {
			std::sort(m_array.begin(), m_array.end());
			const auto k = static_cast<int>(0.9 * (m_array.size() - 1));
			const auto alphaN = 0.9 * m_array.size();
			if (k + 1 < alphaN) {
				m_cache = m_array[k + 1];
			} else if (k + 1 > alphaN) {
				m_cache = m_array[k];
			} else  {
				m_cache = (m_array[k] + m_array[k + 1]) / 2;
			}
		}
		return m_cache.value();
	}

	const char * name() const override {
		return "pct90";
	}

private:
	mutable std::vector<double> m_array;
	mutable std::optional<double> m_cache;
};


class Pct95 : public IStatistics {
public:
	Pct95() {}

	void update(double next) override {
		m_array.push_back(next);
		m_cache.reset();
	}

	double eval() const override {
		if (m_array.empty()) {
			return 0.0;
		}

		if (!m_cache) {
			std::sort(m_array.begin(), m_array.end());
			const auto k = static_cast<int>(0.95 * (m_array.size() - 1));
			const auto alphaN = 0.95 * m_array.size();
			if (k + 1 < alphaN) {
				m_cache = m_array[k + 1];
			} else if (k + 1 > alphaN) {
				m_cache = m_array[k];
			} else  {
				m_cache = (m_array[k] + m_array[k + 1]) / 2;
			}
		}
		return m_cache.value();
	}

	const char * name() const override {
		return "pct95";
	}

private:
	mutable std::vector<double> m_array;
	mutable std::optional<double> m_cache;
};


int main() {
	IStatistics *statistics[] = {new Min, new Max, new Mean, new Std, new Pct90, new Pct95};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < LENGTH_OF(statistics); ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < LENGTH_OF(statistics); ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < LENGTH_OF(statistics); ++i) {
		delete statistics[i];
	}

	return 0;
}