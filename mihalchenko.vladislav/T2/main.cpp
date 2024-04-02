#include <iostream>
// #include <sstream>
#include <vector>
// #include <cctype>
#include <algorithm>
#include <limits>
#include <complex>
#include <iterator>
#include <string>
// #include <bitset>
// #include <iomanip>

namespace mihalchenko
{
	struct DataStruct
	{
		// DataStruct(int key1, std::complex<double> key2, std::string key3) : key1_(key1), key2_(key2), key3_(key3){};
		// DataStruct(int key1, int key2, std::string key3) : key1_(5), key2_(5), key3_("key3"){};
		int key1_;
		std::complex<double> key2_;
		// int key2_;
		std::string key3_;
	};

	struct DelimiterIO
	{
		char expected;
	};

	struct UllBinIO
	{
		int &ref;
	};

	struct ComplexIO
	{
		std::complex<double> &ref;
	};

	struct StringIO
	{
		std::string &ref;
	};

	struct LabelIO
	{
		std::string expected;
	};

	struct KeyIO
	{
		std::string &ref;
	};

	class iofmtguard
	{
	public:
		iofmtguard(std::basic_ios<char> &s);
		~iofmtguard();

	private:
		std::basic_ios<char> &s_;
		char fill_;
		std::streamsize precision_;
		std::basic_ios<char>::fmtflags fmt_;
	};

	std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
	std::istream &operator>>(std::istream &in, UllBinIO &&dest);
	std::istream &operator>>(std::istream &in, ComplexIO &&dest);
	std::istream &operator>>(std::istream &in, StringIO &&dest);
	std::istream &operator>>(std::istream &in, LabelIO &&dest);
	std::istream &operator>>(std::istream &in, DataStruct &dest);
	std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

	bool operator<(const DataStruct &lhs, const DataStruct &rhs);
}

namespace mihalchenko
{
	std::istream &operator>>(std::istream &is, DelimiterIO &&exp)
	{
		std::istream::sentry guard(is);
		if (!guard)
		{
			return is;
		}
		char c = 0;
		is >> c;
		// std::cout << c << " " << exp.expected << std::endl;
		if (c != exp.expected)
		{
			is.setstate(std::ios::failbit);
		}
		return is;
	}

	std::istream &operator>>(std::istream &in, UllBinIO &&dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		// std::cin >> dest.ref;
		// std::cout << "число" << dest.ref << std::endl;
		// return
		// in >> DelimiterIO{'0'} >> DelimiterIO{'b'} >> dest.ref;
		return in >> DelimiterIO{'0'} >> DelimiterIO{'b'} >> dest.ref;
		// std::cout << "число" << dest.ref << std::endl;
		// return in;
	}

	std::istream &operator>>(std::istream &in, ComplexIO &&dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		return in >> dest.ref;
	}

	std::istream &operator>>(std::istream &in, StringIO &&dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
	}

	std::istream &operator>>(std::istream &in, KeyIO &&dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		return std::getline(in, dest.ref, ' ');
	}

	std::istream &operator>>(std::istream &in, LabelIO &&dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		std::string data = "";
		if ((in >> KeyIO{data}) && (data != dest.expected))
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	std::istream &operator>>(std::istream &is, DataStruct &value)
	{
		std::istream::sentry guard(is);
		if (!guard)
		{
			return is;
		}

		/*std::string strKey1 = "key1";
		std::string strKey2 = "key2";
		std::string strKey3 = "key3";*/

		// DataStruct input(0b000000, (.1, .2), "phahaha");
		DataStruct inputDS;
		{
			using sep = DelimiterIO;
			using ull2 = UllBinIO;
			using complex = ComplexIO;
			// using key = KeyIO;
			using str = StringIO;
			using label = LabelIO;

			is >> sep{'('} >> sep{':'};
			for (size_t i = 0; i < 3 && is; ++i)
			{
				std::string key = "";
				is >> label{key};
				if (key == "key1")
				{
					is >> ull2{inputDS.key1_};
				}
				else if (key == "key2")
				{
					is >> complex{inputDS.key2_};
				}
				else if (key == "key3")
				{
					is >> str{inputDS.key3_};
				}
				else
				{
					is.setstate(std::ios::failbit);
				}
				is >> sep{':'} >> sep{')'};
			}
			is >> sep{':'} >> sep{')'};
			/*
			is >> sep{'('} >> sep{':'} >> label{"key1"} >> ull2{inputDS.key1_} >> sep{':'};
			is >> label{"key2"} >> complex{inputDS.key2_};
			is >> sep{':'};
			is >> label{"key3"} >> str{inputDS.key3_};
			is >> sep{':'} >> sep{')'};*/
		}

		// using del = DelimiterIO;
		/*int key1 = 0b000'000;
		std::complex<double> key2 = (.1, 0.);
		std::string key3 = "";*/
		// is >> del{'('} >> del{':'} >> del{' '} >> key1 >> del{':'} >> del{' '} >> key2 >> del{':'} >> del{' '} >> key3 >> del{':'} >> del{')'};
		/*if (is)
		{
			value = DataStruct(key1, key2, key3);
		}
		return is;*/

		if (is)
		{
			value = inputDS;
		}
		return is;
	}

	std::ostream &operator<<(std::ostream &out, const DataStruct &value)
	{
		std::ostream::sentry guard(out);
		if (!guard)
		{
			return out;
		}
		iofmtguard fmtguard(out);
		out << "("
				<< ":key1 "
				<< "0b" << value.key1_ << ":key2 " << value.key2_ << ":key3 " << '"' << value.key3_ << '"' << ":"
				<< ")";
		return out;
	}

	iofmtguard::iofmtguard(std::basic_ios<char> &s) : s_(s),
																										fill_(s.fill()),
																										precision_(s.precision()),
																										fmt_(s.flags())
	{
	}

	iofmtguard::~iofmtguard()
	{
		s_.fill(fill_);
		s_.precision(precision_);
		s_.flags(fmt_);
	}
}

bool mihalchenko::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
	if (lhs.key1_ != rhs.key1_)
	{
		if (lhs.key1_ < rhs.key1_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (lhs.key2_ != rhs.key2_)
	{
		if (abs(lhs.key2_) < abs(rhs.key2_))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (lhs.key3_.size() < rhs.key3_.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int main()
{
	// mihalchenko::DataStruct newStruct(0b000000, (.1, .2), "phahaha");

	/*std::vector<mihalchenko::DataStruct> data;

	std::copy(
			std::istream_iterator< mihalchenko::DataStruct >{std::cin},
			std::istream_iterator<mihalchenko::DataStruct >{},
			std::back_inserter(data));*/

	using mihalchenko::DataStruct;

	std::vector<DataStruct> dataStruct;

	while (!std::cin.eof())
	{
		std::copy(
				std::istream_iterator<DataStruct>{std::cin},
				std::istream_iterator<DataStruct>{},
				std::back_inserter(dataStruct));
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::sort(dataStruct.begin(), dataStruct.end());
	std::copy(
			std::begin(dataStruct),
			std::end(dataStruct),
			std::ostream_iterator<DataStruct>(std::cout, "\n"));

	/*mihalchenko::DataStruct newStruct;
	if (!(std::cin >> newStruct))
	{
		std::string str;
		std::cin >> str;
		std::cout << str << "!" << std::endl;
		std::cout << newStruct << "\n";

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!(std::cin >> newStruct))
		{
			std::cerr << "Error\n";
			std::cout << newStruct << "\n";
			return 1;
		}
	}
	std::cout << newStruct << "\n";*/
	return 0;
}
