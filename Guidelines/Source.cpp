#include <vector>
#include <iostream>
#include <memory>
#include <string>

namespace VectorPerformance
{
	struct SampleClass
	{
	    SampleClass(int val) : value(val)
		{
		}

		SampleClass(const SampleClass& other) : value(other.value)
		{
			std::cout << "Copied" << std::endl;
		}

	private:
		int value;
	};
}

namespace InitializerList
{
	struct SampleClass
	{
		explicit SampleClass(int i) : value(i)
		{
			std::cout << value << std::endl;
			std::cout << value << std::endl;
		}

	private:
		int value;
	};
}

namespace HeapAllocation
{
	struct SampleClass
	{
		explicit SampleClass()
		{
			heapAllocatedInt = new int(666);
		}

		~SampleClass()
		{
			delete heapAllocatedInt;
		}

		void PrintInt()
		{
			std::cout << *heapAllocatedInt << std::endl;
		}

		void SetInt(int val)
		{
			*heapAllocatedInt = val;
		}

		int * GetInt() const
		{
			return heapAllocatedInt;
		}

	private:
		int * heapAllocatedInt;
	};
}

template<typename T>
class ScopedPointer
{
	T * _ptr;

public:
	explicit ScopedPointer(T * ptr) : _ptr(ptr)
	{
	}

	~ScopedPointer()
	{
		std::cout << "Destroyed " << *_ptr << std::endl;
		delete _ptr;
	}

};


auto main(int argc, char **argv) -> int
{
	if (false)
	{
		using namespace VectorPerformance;

		std::vector<SampleClass> sampleVector;

		sampleVector.emplace_back(1);
		sampleVector.emplace_back(2);
		sampleVector.emplace_back(3);
	}

	if (false)
	{
		using namespace InitializerList;
		SampleClass sampleClass(2);
	}

	if (false)
	{
		using namespace HeapAllocation;

		// Create instance
		SampleClass sampleClass;
		std::cout << "Before copying: ";
		sampleClass.PrintInt();

		// Create another instance with copying values of previous instance
		SampleClass copied = sampleClass;
		std::cout << "After copying: ";
		sampleClass.PrintInt();
		
		// Change the value
		sampleClass.SetInt(12);
		std::cout << "After changing the value of one instance: " << std::endl;
		
		std::cout << "Instance one: ";
		sampleClass.PrintInt();

		std::cout << "Instance two: ";
		copied.PrintInt();

		std::cout << "Bummer..." << std::endl;
	}

	{
		ScopedPointer<int> scoped(new int(5));
	}

	std::cin.get();
}