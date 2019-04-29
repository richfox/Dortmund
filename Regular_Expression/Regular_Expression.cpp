// Regular_Expression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <boost\regex.hpp>
#include <set>
#include <regex>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include "..\Tool\basedef.h"
#include "..\Tool\Debug.h"

using namespace std;



namespace
{
	struct TT
	{
		TT(string n,int i):name(n),index(i){}

		string name;
		int index;
	};

    template<typename T>
    struct KeyType
    {
       typedef T Type;
    };

    template<typename T>
    struct TypeInfo
    {};


   template<>
   struct TypeInfo<int>
   {
      static const wchar_t* TypeName;
   };

   template<>
   struct TypeInfo<int*>
   {
      static const wchar_t* TypeName;
   };

   template<>
   struct TypeInfo<int[8]>
   {
      static const wchar_t* TypeName;
   };

   template<>
   struct TypeInfo<wstring>
   {
      static const wchar_t* TypeName;
   };

   template<>
   struct TypeInfo<wstring*>
   {
      static const wchar_t* TypeName;
   };

   template<>
   struct TypeInfo<wstring[32]>
   {
      static const wchar_t* TypeName;
   };

   const wchar_t* TypeInfo<int>::TypeName = L"int";
   const wchar_t* TypeInfo<int*>::TypeName = L"int*";
   const wchar_t* TypeInfo<int[8]>::TypeName = L"int[8]";
   const wchar_t* TypeInfo<wstring>::TypeName = L"wstring";
   const wchar_t* TypeInfo<wstring*>::TypeName = L"wstring*";
   const wchar_t* TypeInfo<wstring[32]>::TypeName = L"wstring[32]";


	ostream& operator << (ostream& os,const TT& tt)
	{
		os << "<" << tt.index << "> " << tt.name;
		return os;
	}

	ostream& operator << (ostream& os,const shared_ptr<TT>& tt)
	{
		os << "<" << tt->index << "> " << tt->name;
		return os;
	}

	bool operator < (const TT& t1,const TT& t2)
	{
		if (t1.index == t2.index)
			return t1.name < t2.name;
		else
			return t1.index < t2.index;
	}

	bool operator < (const shared_ptr<TT>& t1,const shared_ptr<TT>& t2)
	{
		if (t1->index == t2->index)
			return t1->name < t2->name;
		else
			return t1->index < t2->index;
	}

	inline size_t func1(wchar_t* para1,size_t s1,wchar_t* para2,size_t s2)
	{
		auto diffpara = para1-para2;
		return s1-s2;
	}

	template<size_t size1,size_t size2>
	inline size_t func2(wchar_t(&para1)[size1],wchar_t(&para2)[size2])
	{
		auto diffpara = para1-para2;
		return size1-size2;
	}
}

namespace
{
   class DRImpBase
   {
   public:
      DRImpBase(int key)
         :_key(key)
      {}

      virtual ~DRImpBase()
      {}

      virtual void Calc()
      {
         _key += 2;
      };

      const int Get() const
      {
         return _key;
      }

   protected:
      int _key;
   };

   template<int Tag>
   class DRImp : public DRImpBase
   {
   public:
      DRImp(int key)
         :DRImpBase(key)
      {}

      virtual ~DRImp()
      {}

      void Calc()
      {
         if (Tag == 0)
            _key++;
         else if (Tag == 1)
            _key--;
      }
   };

   typedef DRImp<0> DImp;
   typedef DRImp<1> RImp;


   template<int Tag>
   class DDRRImp sealed : public DRImp<Tag>
   {
   public:
      DDRRImp(int key)
         :DRImp<Tag>(key)
      {}

      ~DDRRImp()
      {}

      void Calc()
      {
         if (Tag == 0)
            _key *= 2;
         else if (Tag == 1)
            _key /= 2;
      }
   };

   typedef DDRRImp<0> DDImp;
   typedef DDRRImp<1> RRImp;
}

namespace
{
	class A
	{
	public:
		A()
		{
			n = 0;
		}

		A(const A& a)
		{
			n = a.n;
		}

	private:
		int n;
	};

	class B: public A
	{
	public:
		B():A()
		{
			m = 0;
		}

		const B& operator=(const B& b)
		{
			m = b.m;
			return *this;
		}

	private:
		int m;
	};

	

	class Base
	{
	public:
		virtual void f()
		{
			cout << "Base::f" << endl;
		}

		virtual void g()
		{
			cout << "Base::g" << endl;
		}

		int a;
		int* b;

	private:
		virtual void h()
		{
			cout << "Base::h" << endl;
		}
	};

	class Derive: public Base
	{
	public:
		void f1()
		{
			cout << "Derive::f1" << endl;
		}
	};


	void insert_Fenster(int pos,wstring name);
	wstring get_Fenster_name(int pos);
	class Fenster
	{
	public:
		Fenster():_name(L"")
		{}
		Fenster(wstring name)
			:_name(name)
		{}

		void reload()
		{
			_name;
			insert_Fenster(1,L"tempFenster");
			wstring tmp = get_Fenster_name(1);
			_name = tmp;
		}

		wstring get_name()
		{
			return _name;
		}

	private:
		wstring _name;
	};

	class FensterManager
	{
	public:
		bool has(int pos)
		{
			if (_mapFenster.find(pos)!=_mapFenster.end())
				return true;
			else
				return false;
		}

		void insert(int pos,wstring name)
		{
			if (has(pos))
			{
				//_mapFenster.erase(pos);
				std::swap(_mapFenster[pos],Fenster(name));
			}
			else
				_mapFenster.insert(make_pair(pos,Fenster(name)));
		}

		Fenster& get_Fenster(int pos)
		{
			return _mapFenster.at(pos);
		}

	private:
		static map<int,Fenster> _mapFenster;
	};

	void insert_Fenster(int pos,wstring name)
	{
		FensterManager fm;
		fm.insert(pos,name);
	}

	void reload_Fenster(int pos)
	{
		FensterManager fm;
		if (fm.has(pos))
			fm.get_Fenster(pos).reload();
	}

	wstring get_Fenster_name(int pos)
	{
		wstring name;

		FensterManager fm;
		if (fm.has(pos))
			name = fm.get_Fenster(pos).get_name();

		return name;
	}


    class Tmm
    {
    public:
       Tmm(std::wstring t)
          :_t(t)
       {}

    private:
       std::wstring _t;
    };

    Tmm to_tmm()
    {
       return L"test";
    }

    class LuisaAndLukas
    {
    public:
       LuisaAndLukas(const std::wstring& l1,const std::wstring& l2)
          :_luisa(l1),
          _lukas(l2)
       {}

       LuisaAndLukas(const LuisaAndLukas& other)
          :_luisa(other.GetLuisa()), //这里对象other通过public函数间接调用了private字段
          _lukas(other._lukas) //这里对象other直接调用了private字段，也是可以的！！！
       {}

       std::wstring GetLuisa() const
       {
          return _luisa;
       }

       std::wstring GetLukas() const
       {
          return _lukas;
       }

    private:
       std::wstring _luisa;
       std::wstring _lukas;
    };


	void overloaded(const int& arg)
	{
		std::cout << "by lvalue\n";
	}

	void overloaded(int&& arg)
	{
		std::cout << "by rvalue\n";
	}

	//ref. collapsing rules
	//T& & -> T&
	//T& && -> T&
	//T&& & -> T&
	//T&& && -> T&&
	template<typename T>
	void moveforward(T&& arg)
	{
		std::cout << "via std::forward: ";
		overloaded(std::forward<T>(arg));

		std::cout << "via std::move: ";
		overloaded(std::move(arg)); //std::move的本质是去掉参数的&，然后转换成&&

		std::cout << "via static cast to T&: ";
		overloaded(static_cast<T&>(arg));

		std::cout << "via static cast to T&&: ";
		overloaded(static_cast<T&&>(arg)); //类似于std::forward

		std::cout << "by simple passing: ";
		overloaded(arg); //有名字的右值引用参数在函数体内被当做左值引用
	}

   //test template polymorphism //isd-xfu, 2.3.2016
   template<typename T>
   class TA
   {
   public:
	   virtual void f1() {cout << "TA f1() called" << endl;}
	   virtual void f2() = 0 {cout << "TA f2() called" << endl;}
	   virtual void f3(T t) {cout << "TA f3(T) called" << endl;}
   };

   template<typename T>
   class TB : public TA<T>
   {
   public:
	   virtual void f1() {cout << "TB f1() called" << endl;}
	   virtual void f2() override {cout << "TB f2() called" << endl;}
	   virtual void f3(T t) {cout << "TB f3(T) called" << endl;} 
   };

   class TC : public TA<int>
   {
   public:
	   virtual void f1() {cout << "TC f1() called" << endl;}
	   virtual void f2() override {cout << "TC f2() called" << endl;}
	   virtual void f3(int t) {cout << "TC f3(int) called" << endl;} 
   };

   //test overload function //isd-xfu, 28.7.2016
   void funcOL(int i=1,int j=2)
   {
      cout << i << j << endl;
   }

   void funcOL(int i)
   {
      cout << i << endl;
   }

   //test overload class //isd-xfu, 28.7.2016
   struct Nothing
   {};
   template<typename T0=Nothing,typename T1=Nothing,typename T2=Nothing>
   class COL
   {
   public:
      COL()
      {
         cout << "COL" << endl;
      }
   };

   template<typename T0>
   class COL<T0>
   {
   public:
      T0 _t0;
      
      COL()
      {
         
         cout << "COL<T0>" << endl;
      }

      COL(T0 t0)
         :_t0(t0)
      {
         cout << _t0 << endl;
      }
   };

   template<typename T0,typename T1>
   class COL<T0,T1>
   {
   public:
      T0 _t0;
      T1 _t1;

      COL()
      {
         cout << "COL<T0,T1>" << endl;
      }

      COL(T0 t0,T1 t1)
         :_t0(t0),_t1(t1)
      {
         cout << _t0 << _t1 << endl;
      }
   };
}

map<int,Fenster> FensterManager::_mapFenster;


//12.10.2017
//test const
class Leg
{
public:
   Leg(int idx)
      :subleg(new Leg(0)),
      _idx(idx)
   {}

   ~Leg()
   {
      delete subleg;
   }

   void SetIdx(int idx)
   {
      _idx = idx;
   }

   int GetIdx() const
   {
      return _idx;
   }

private:
   int _idx;
public:
   Leg* subleg;
};

void setLeg(const Leg& leg)
{
   //leg.SetIdx(8); //error: 因为const，这里不能调用
   leg.GetIdx();
   leg.subleg->SetIdx(8); //但是子对象却能够调用
   //leg.subleg = new Leg(10); //error: const在这里要求的是指针指向的地址不变！！！
}


class TPoint1
{
public:
   TPoint1(int x,int y)
   {
      _X = x;
      _Y = y;
   }
   TPoint1(const TPoint1& p)
   {
      _X = p._X;
      _Y = p._Y;
      cout << "Copy constructor called\n";
   }
   TPoint1& operator=(const TPoint1& p)
   {
      _X = p._X;
      _Y = p._Y;
      cout << "Copy operator called\n";
      return *this;
   }
   TPoint1 operator[](const TPoint1& p)
   {
      _X = p._X;
      _Y = p._Y;
      cout << "Copy operator called\n";
      return *this;
   }
   ~TPoint1()
   {
      cout << "Destructor called\n";
   }
   int Xcoord()
   {
      return _X;
   }
   int Ycoord()
   {
      return _Y;
   }
private:
   int _X, _Y;
};

TPoint1 fun(TPoint1 Q)
{
   cout << "ok\n";
   int x = Q.Xcoord() + 10;
   int y = Q.Ycoord() + 15;
   TPoint1 R(x,y);
   return R;
}


void _tmain(int argc, _TCHAR* argv[])
{
	///////////////TEST C++多态////////////////////
	Base base1;
	base1.a=1;
	base1.b=&(base1.a);
	cout << "size of Base: " << sizeof(base1) << endl;
	cout << "address of V-Table:" << (&base1) << "   " //(&base1) isnt pointer
		<< (size_t*)(&base1) //(size_t*)(&base1) is pointer
		<< endl;
	cout << "address of first function in V-Table:"
		<< (size_t*)((size_t*)((size_t*)(&base1))[0])[0] << "   " 
		<< reinterpret_cast<size_t*>(reinterpret_cast<size_t*>(reinterpret_cast<size_t*>(&base1)[0])[0]) << "   "
		<< (size_t*)*(size_t*)*(size_t*)(&base1) << "   "
		<< endl;
	cout << "address of second function in V-Table:"
		<< (size_t*)((size_t*)((size_t*)(&base1))[0])[1] << "   " 
		<< reinterpret_cast<size_t*>(reinterpret_cast<size_t*>(reinterpret_cast<size_t*>(&base1)[0])[1]) << "   "
		<< (size_t*)*((size_t*)*(size_t*)(&base1)+1) << "   "
		<< endl;

	typedef void (*fpointer)();
	fpointer pFunc = NULL;

	pFunc = (fpointer)((size_t*)((size_t*)(&base1))[0])[0];
	(*pFunc)();
	pFunc = reinterpret_cast<fpointer>(reinterpret_cast<size_t*>(reinterpret_cast<size_t*>(&base1)[0])[1]);
	(*pFunc)();
	pFunc = (fpointer)*((size_t*)*(size_t*)(&base1)+2);
	(*pFunc)();


	///////////////TEST TEMP 测试正则表达式////////////////////
	wstring filename = L"A2HF1_16.vaa";

	//erstetzen "?" durch ".?"
	//ersetzen "*" durch ".*"
	boost::wregex expr(L"a.?h.*6.*vaa.*",boost::regex::perl|boost::regex::icase);

	boost::wsmatch match;

	bool res = boost::regex_match(filename,match,expr);

	cout<<res<<endl;

	///////////////TEST TEMP 测试STD正则表达式////////////////////
	wstring text = L"R()12.3";
	wregex rx = wregex(L"\\(.?1.*\\.");
	
	text = regex_replace(text,rx,wstring(L"aa"),regex_constants::format_first_only);

    rx = wregex(L"^[0-9]{1,10}$");
    for (int i=-10; i<20; i++)
    {
       wchar_t tmp[8];
       _itow_s(i,tmp,10);
       res = regex_search(tmp,rx);
    }


	///////////////TEST TEMP 测试重载运算符, set_intersection和list,set容器的配合用法////////////////////
	shared_ptr<TT> t1[] = {shared_ptr<TT>(new TT("t2",2)),shared_ptr<TT>(new TT("t4",4))};
	shared_ptr<TT> t2[] = {shared_ptr<TT>(new TT("t4",4)),shared_ptr<TT>(new TT("t2",2))};
	list<shared_ptr<TT>> v1(t1,t1+_countof(t1));
	v1.sort();
	list<shared_ptr<TT>> v2(t2,t2+_countof(t2));
	v2.sort();

	auto it = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),v1.begin(),[&](shared_ptr<TT> e1,shared_ptr<TT> e2)->bool
	{
		if (e1->index == e2->index)
			return e1->name < e2->name;
		else
			return e1->index < e2->index;
	});
	v1.erase(it,v1.end());
	ostream_iterator<shared_ptr<TT>> ofile(cout," ");
	copy(v1.begin(),v1.end(),ofile);
	cout<<endl;

	int t3[] = {0,1,2,3};
	int t4[] = {0,3,4,6};
	list<int> v3(t3,t3+_countof(t3));
	v3.sort(); //set_intersection 所用容器必须排序
	list<int> v4(t4,t4+_countof(t4));
	v4.sort();
	
	auto it2 = set_intersection(v3.begin(),v3.end(),v4.begin(),v4.end(),v3.begin());
	v3.erase(it2,v3.end());

	set<int> v5(t3,t3+_countof(t3));
	set<int> v6(t4,t4+_countof(t4));
	list<int> res2;
	auto it3 = set_intersection(v5.begin(),v5.end(),v6.begin(),v6.end(),inserter(res2,res2.begin()));

	///////////////TEST TEMP 测试构造函数////////////////////
	B b1;
	B b2(b1);
	B b3 = b1;




	///////////////TEST TEMP 泛型函数////////////////////
	wchar_t tmp[1024] = L"test";
	wchar_t tmp2[512] = L"TEST";
	size_t s = func1(tmp,1024,tmp2,512);
	size_t s2 = func2(tmp,tmp2);

	///////////////c++0x range based for loops////////////////////
	//http://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer#foreach


	std::unique_ptr<int> p1(new int(42));
	std::unique_ptr<int> p2 = std::move(p1); // transfer ownership

	cout << p1.get() << endl; 
	cout << *p2 << endl;

	auto p3 = make_shared<int>(242);
	cout << *p3 << endl;

	int arr[] = {1,2,3};
	std::for_each(std::begin(arr), std::end(arr), [](int n)
	{
		std::cout << n << std::endl;
	});

	auto pos = std::find_if(std::begin(arr), std::end(arr), [](int n) 
	{
		return n%2==1;
	});
	if(pos != std::end(arr))
		std::cout << *pos << std::endl;

//isd-xfu, 10.10.2013
	insert_Fenster(1,L"xfu");
	reload_Fenster(1);

//isd-xfu, 16.10.2013
	unique_ptr<int> i(new int(8));
	unique_ptr<int> i2 = move(i);
    //unique_ptr<int> i3 = i2; //Error

	unique_ptr<int []> i4(new int[2]);
	i4[0] = 1;
	i4[2] = 3;

	shared_ptr<int> j(new int(8));
	shared_ptr<int> j2 = j;
	shared_ptr<int> j3 = move(j);
	shared_ptr<int> j4 = j;

	shared_ptr<int> j5 = make_shared<int>(9);

//isd-xfu, 9.4.2014
	__time64_t t;
	_time64(&t);

	__time64_t beginTime = 1397058688; //Dortmund 9.4.2014   17:50
	__time64_t maxTime = INT_MAX;
	t = (maxTime+1)*1+beginTime;
	__time64_t diff = t-beginTime;
	if (diff > INT_MAX)
	{
		int tmp = int(diff);
		int tmp2 = 0;
	}

//isd-xfu, 16.7.2014
	class AA
	{
	public:
		virtual void fpub(){}
	protected:
		virtual void fpro(){}
	private:
		void fpri(){}
	};

	class BB : private AA
	{
	public:
		void foo()
		{
			fpub();
			AA::fpro();
			//fpri();
		}
	};

	class CC : public AA
	{
	public:
		virtual void fpro(){AA::fpro();}

		virtual void tmp(){}

	private:
		virtual void fpub(){AA::fpub();}
	};

	unique_ptr<AA> aa(new CC);
	aa->fpub();

	AA aa2 = CC();
	aa2.fpub();

	CC cc;
	cc.fpro();
	cc.tmp();
	//cc.fpub();

    wstring ori = L"123456789";
    ori.replace(1,2,L"tttt");
    ori.replace(1,4,wstring(L"tt"));

#define TEMP L"%%"
	int temp1 = _countof(TEMP);
	int temp2 = int(wcslen(TEMP));

    const std::type_info& ti = typeid(0.4*4);
    auto tname = ti.name();

    const wstring wtext = L"text";
    LPWSTR ttext;
    ttext = const_cast<wchar_t*>(wtext.c_str());

    //test reflector //isd-xfu, 16.6.2015
   struct MyStruct
   {
      int a;
      double b;
      std::wstring c;
      int* ap;
      double* bp;
      std::wstring* cp;
      int aa[8];
      double ba[16];
      std::wstring ca[32];
   };

   std::cout << typeid(int*).name() << std::endl;
   std::cout << typeid(((MyStruct*)0)->ap).name() << std::endl;
   std::cout << typeid(std::wstring[32]).name() << std::endl;
   std::cout << typeid(((MyStruct*)0)->ca).name() << std::endl;
    
   wstring ss = TypeInfo<decltype(((MyStruct*)0)->ca)>::TypeName;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->a)>::TypeName << std::endl;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->ap)>::TypeName << std::endl;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->aa)>::TypeName << std::endl;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->c)>::TypeName << std::endl;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->cp)>::TypeName << std::endl;
   std::cout << TypeInfo<decltype(((MyStruct*)0)->ca)>::TypeName << std::endl;

   //test virtual function 测试多态 //isd-xfu, 20.7.2015
   class VA
   {
   public:
      void run()
      {
         fuck();
         foo();
      }

      virtual void fuck()
      {
         std::cout << "VA::fuck()" << std::endl;
      }

   private:
      virtual void foo()
      {
         std::cout << "VA::foo()" << std::endl;
      }
   };

   class BA : public VA
   {
   public:
      void fuck()
      {
         std::cout << "VB::fuck()" << std::endl;
      }

   private:
      virtual void foo()
      {
         std::cout << "BA::foo()" << std::endl;
      }
   };

   BA ba;
   ba.run(); //这种情况下不需要用指针或者引用就可以实现多态！！！
   unique_ptr<BA> uba(new BA);
   uba->run(); //当然用了指针或者引用也可以
   VA va = BA();
   va.run(); //va并不是BA的对象，BA的匿名对象被切割赋值给va，所以不能实现多态！！！
   unique_ptr<VA> uva(new BA);
   uva->run(); //用指针实现多态
   VA& rva = BA();
   rva.run(); //用引用实现多态

   //test RTTI
   if (BA* ba = dynamic_cast<BA*>(uva.get()))
   {
      std::cout << "uva is BA" << std::endl;
   }
   if (typeid(*uva) == typeid(BA))
   {
      std::cout << typeid(*uva).name() << std::endl;
      std::cout << typeid(BA).name() << std::endl;
      std::cout << typeid(VA).name() << std::endl;
      std::cout << typeid(uva.get()).name() << std::endl;
      std::cout << typeid(BA*).name() << std::endl;
   }

   std::unique_ptr<TA<int>> upta(new TB<int>);
   upta->f1();
   upta->f2();
   upta->f3(int(0));

   upta.reset(new TC);
   upta->f1();
   upta->f2();
   upta->f3(int(0));

   //test hash //isd-xfu, 22.7.2015
   std::unordered_map<int, std::string> dict;
   dict.insert(std::make_pair(1,"one"));
   dict.insert(std::make_pair(2,"two"));
   dict.insert(std::make_pair(3,"three"));
   dict.insert(std::make_pair(4,"four"));
   dict.insert(std::make_pair(11,"one"));

   bool ok = dict.insert(make_pair(1,"another one")).second;
   std::cout << "inserting 1 -> \"another one\" " 
      << (ok ? "succeeded" : "failed") << '\n';

   std::cout << "contents:\n";
   for(auto& p: dict)
      std::cout << " " << p.first << " => " << p.second << '\n';

   struct Pos
   {
      int x;
      int y;
      int z;
      __time64_t t;

      Pos()
         :x(0),y(0),z(0),t(0)
      {}

      Pos(const int& x,const int& y,const int& z,const __time64_t& t)
         :x(x),y(y),z(z),t(t)
      {}

      bool operator==(const Pos& pos) const
      {
         return x==pos.x && y==pos.y && z==pos.z && t==pos.t;
      }
   };

   struct PosHasher
   {
      size_t operator()(const Pos& position) const
      {
         std::hash<int> hashFn;
         return position.t^((hashFn(position.z)<<16)|(hashFn(position.y)<<8)|(hashFn(position.x)));
      }
   };

   std::cout <<PosHasher()(Pos()) << std::endl;

   std::unordered_map<Pos,std::string,PosHasher> dictPos;
   dictPos.insert(std::make_pair(Pos(),"pos0"));
   dictPos.insert(std::make_pair(Pos(10,10,10,1397058688),"pos1"));
   
   Pos pos2;
   pos2.x = 100;
   pos2.y = 100;
   pos2.z = 100;
   _time64(&t);
   pos2.t = t;
   dictPos.insert(std::make_pair(pos2,"pos2"));

   for (const auto& dp : dictPos)
      std::cout << dictPos.hash_function()(dp.first) << std::endl;

   //isd-xfu, 4.9.2015
   Tmm _tmm = to_tmm(); //隐式赋值

   LuisaAndLukas lulu(L"luisa",L"lukas");
   LuisaAndLukas lulucopy(lulu);

   moveforward(5);
   int xfu = 5;
   moveforward(xfu);



   //isd-xfu, 19.11.2015
   //difference between find and find_first_of
   wstring to_search = L"mississippi";
   wstring to_find[] = {L"ss",L"is"};
   vector<wstring> findfirstres;
   vector<wstring> findres;
   for (const auto& t : to_find)
   {
	   auto pos = to_search.find_first_of(t);
	   while (pos != wstring::npos)
	   {
		   findfirstres.push_back(to_search.substr(pos,t.size()));
		   pos = to_search.find_first_of(t,pos+t.size());
	   }
   }

   for (const auto& t : to_find)
   {
	   auto pos = to_search.find(t);
	   while (pos != wstring::npos)
	   {
		   findres.push_back(to_search.substr(pos,t.size()));
		   pos = to_search.find(t,pos+t.size());
	   }
   }
   
   vector<wstring> rres(3);
   rres;

   //isd-xfu, 30.03.2016 
   //test union
   enum UNIONENUM
   {
      FIRST = 0x20494542,
      SECOND = 0x474e494f,
      THIRD = 0x00000a21
   };
   union
   {
      int ig[3];
      char s[12];
      wchar_t ss[6];
      UNIONENUM ue[3];
   }tunion;
   tunion.ig[0] = 0x20494542;
   tunion.ig[1] = 0x474e494a;
   tunion.ig[2] = 0x00000a21;
   cout << tunion.s << tunion.ss << tunion.ue[1] << endl;

   
   //isd-xfu, 19.07.2016 
   //test virtual class
   //------Avc
   //-----/---\
   //---Bvc---Cvc
   //-----\---/
   //------Dvc
   class Avc
   {
   public:
      Avc()
      {
         cout << "empty" << endl;
      }
      Avc(const char* s)
      {
         cout << s << endl;
      }

      virtual void foo()
      {}
   };

   class Bvc : virtual public Avc
   {
   public:
      Bvc(const char* s1,const char* s2)
         :Avc(s1)
      {
         cout << s2 << endl;
      }

      virtual void foo()
      {}
   };

   class Cvc : virtual public Avc
   {
   public:
      Cvc(const char* s1,const char*s2)
         :Avc(s1)
      {
         cout << s2 << endl;
      }
   };

   class BBvc : public Avc
   {
   public:
      BBvc(const char* s1,const char* s2)
         :Avc(s1)
      {
         cout << s2 << endl;
      }
   };

   class CCvc : public Avc
   {
   public:
      CCvc(const char* s1,const char*s2)
         :Avc(s1)
      {
         cout << s2 << endl;
      }
   };

   class Dvc : public Bvc, public Cvc
   {
   public:
      Dvc(const char* s1,const char*s2,const char* s3,const char* s4)
         :Bvc(s1,s2),
         Cvc(s1,s3),
         Avc(s1)
      {
         cout << s4 << endl;
      }
   };

   class DDvc : public BBvc, public CCvc
   {
   public:
      DDvc(const char* s1,const char*s2,const char* s3,const char* s4)
         :BBvc(s1,s2),
         CCvc(s1,s3)
      {
         cout << s4 << endl;
      }
   };

   class DDDvc : public BBvc, public Cvc
   {
   public:
      DDDvc(const char* s1,const char*s2,const char* s3,const char* s4)
         :BBvc(s1,s2),
         Cvc(s1,s3)
      {
         cout << s4 << endl;
      }
   };

   //虚基类先于非虚基类构造
   //调用顺序为Avc,Bvc,Cvc,Dvc
   Dvc dvc("class Avc","class Bvc","class Cvc","class Dvc");
   //钻石性质继承关系里子类调用最近的虚函数
   dvc.foo();
   //如果不用虚基类
   //调用顺序为Avc,Bvc,Avc,Cvc,Dvc
   DDvc ddvc("class Avc","class Bvc","class Cvc","class Dvc");
   //如果一半用虚基类
   //调用顺序为empty,Avc,Bvc,Cvc,Dvc
   DDDvc dddvc("class Avc","class Bvc","class Cvc","class Dvc");

   //------Avc
   //-----/---\
   //---Bvc---Cvc
   //---/------/
   //-Evc-----/
   //---\----/
   //-----Fvc
   class Evc : public Bvc
   {
   public:
      Evc(const char* s1,const char* s2,const char* s3)
         :Bvc(s1,s2),
         Avc(s1)
      {
         cout << s3 << endl;
      }
   };

   class Fvc : public Cvc, public Evc
   {
   public:
      Fvc(const char* s1,const char*s2,const char* s3,const char* s4,const char* s5)
         :Cvc(s1,s2),
         Evc(s1,s3,s4),
         Avc(s1) //Avc是虚基类要额外构造
      {
         cout << s5 << endl;
      }
   };

   cout << endl;
   //虚基类先于非虚基类构造
   //调用顺序为Avc,Cvc,Evc,Fvc
   Fvc fvc("class Avc","class Cvc","class Bvc","class Evc","class Fvc");

   //------Avc
   //-----/---\
   //---Bvc---Cvc
   //---/------/
   //-Gvc-----/
   //---\----/
   //-----Hvc
   class Gvc : virtual public Bvc //Bvc是虚基类
   {
   public:
      Gvc(const char* s1,const char* s2,const char* s3)
         :Bvc(s1,s2),
         Avc(s1)
      {
         cout << s3 << endl;
      }
   };

   class Hvc : public Gvc, virtual public Cvc//virtual在这个钻石构造中只会影响Cvc，Gvc的调用顺序，有先调用Cvc，没有先调用Gvc
   {
   public:
      Hvc(const char* s1,const char*s2,const char* s3,const char* s4,const char* s5)
         :Gvc(s1,s2,s3),
         Cvc(s1,s4),
         Bvc(s1,s2), //Bvc是虚基类要额外构造
         Avc(s1) //Avc是虚基类要额外构造
      {
         cout << s5 << endl;
      }
   };

   cout << endl;
   //虚基类先于非虚基类构造
   //调用顺序为Avc,Bvc,Cvc,Gvc,Hvc
   Hvc hvc("class Avc","class Bvc","class Cvc","class Gvc","class Hvc");

   //isd-xfu, 28.07.2016 
   //test template
   funcOL();
   //funcOL(2); //error: 不确定加载哪个重载函数
   funcOL(3,4);

   COL<int> col1; //注意这里的类型int不能和COL类中的Nothing一样
   COL<int,int> col2;
   COL<int,int,int> col3;
   COL<> col4; //是什么类型尚不清楚，要去问

   //isd-xfu, 03.08.2016 
   //test 继承后的访问性质
   //不管是哪种继承，都是基类的公有成员和保护成员可被派生类访问
   class AAA
   {
   public:
      AAA():_aaa(0){}
      virtual ~AAA(){}
      void  tmp()
      {
         int t = test();
      }

      virtual void foo()
      {
         _aaa++;
      }

   private:
      virtual int test() = 0;
      int _aaa;
   };

   class AAB : private AAA
   {
   public:
      AAB():_bbb(1){}
      ~AAB(){}
      void tmp2()
      {
         //int t = _aaa; //error
         tmp(); //private继承后，在继承类中基类的public成员依然可以调用！！
      }
   private:
      virtual int test()
      {
         return _bbb;
      }
      int _bbb;
   };

   AAB aab;
   aab.tmp2();
   //aab.tmp(); //error： private继承后，在继承类对象中基类的private成员不可以调用！！
   // AAA* aaaa = new AAB; //error: private继承不可以，原因不明！！

   class AAC : public AAA
   {
   public:
      AAC():_ccc(2){}
      virtual ~AAC(){}

      virtual void foo()
      {
         _ccc++;
      }

   private:
      virtual int test()
      {
         return _ccc;
      }
      int _ccc;
   };

   class AAD : public AAC
   {
   public:
      AAD():AAC()
      {}

      virtual ~AAD()
      {}
   };

   AAA* aaa = new AAC;
   aaa->tmp();//test虚函数尽管在基类中是private，还是可以有多态的效果！！
   delete aaa;

   aaa = new AAD;
   aaa->foo(); //如果虚函数没有重载，就近调用基类的
   delete aaa;

   ////isd-xfu, 18.08.2016 
    typedef std::tuple<int, double, int, double> Mytuple; 

    Mytuple c0(0, 1, 2, 3); 
    auto c1 = std::make_tuple(4, 5, 6, 7); 
    auto c2 = std::make_tuple(4, 5, 6, 7, 8);

    std::cout << std::boolalpha << " " << (c0 < c0); 
    std::cout << std::endl; 
    std::cout << std::boolalpha << " " << (c0 < c1); 
    std::cout << std::endl;
    //std::cout << std::boolalpha << " " << (c1 < c2); //error
    std::cout << std::endl;


    ///isd-xfu, 29.11.2016 
    std::tr2::sys::path path(L"C:\\temp\\temp\\");
    wstring wstrpath = path.parent_path().wstring();
    wstrpath = path.parent_path().parent_path().wstring();
    wstrpath = path / std::tr2::sys::path(L"temp");
    wstrpath = path.parent_path() / std::tr2::sys::path(L"temp");



    ELAPSED_START;
    //Fibonacci数列
    std::function<int(int)> fib = [&](int x)->int
    {
       return x<2 ? 1 : fib(x-1)+fib(x-2); 
    };
    std::cout<<fib(3)<<std::endl;
    ELAPSED_END;

    //test vector::emplace
    struct Child
    {
       std::string _name;
       std::string _birthday;
       std::string _nationality;

       Child(std::string name,std::string birthday,std::string nationality)
          :_name(name),
          _birthday(birthday),
          _nationality(nationality)
       {
          std::cout << "being constructed.\n";
       }

       Child(Child&& other)
          :_name(std::move(other)._name),
          _birthday(std::move(other)._birthday),
          _nationality(std::move(other)._nationality)
       {
          std::cout << "being moved.\n";
       }
    };

    std::vector<Child> children;
    children.reserve(2); //保证添加元素不会在内部触发扩展buffer的代码，否则会有较多的move调用，可以注释后比较查看
    children.emplace_back("Lukas","09.07.2010","Chinese");
    children.push_back(Child("Luisa","11.09.2015","German"));

    for (const Child& child : children)
    {
       std::cout << child._name << " was born in " << child._birthday.c_str() << std::endl;
       CONSOLE_MESSAGE(std::wstring(child._nationality.begin(),child._nationality.end()).c_str());
       wstringstream wss;
       wss << __FILE__ << L":" << __LINE__ << L":" << child._nationality.c_str() << L"\n";
       CONSOLE_MESSAGE(wss.str().c_str());
    }

#ifdef  _WIN64
    static_assert(sizeof(void*)==8,"64 bit pointer.");
#else
    static_assert(sizeof(void*)==4,"32 bit pointer.");
#endif

    //test template<int>
    DImp di(6);
    di.Calc();
    RImp ri(8);
    ri.Calc();
    cout << di.Get() << "\t" << ri.Get() << endl;
    DRImpBase* dib = new DRImpBase(1024);
    dib->Calc();
    DRImpBase* dib2 = new DImp(1024);
    dib2->Calc();
    DRImpBase* dib3 = new RImp(1024);
    dib3->Calc();
    DRImpBase* dib4 = new DDImp(1024);
    dib4->Calc();
    DRImpBase* dib5 = new RRImp(1024);
    dib5->Calc();
    cout << dib->Get() << "\t" << dib2->Get() << "\t" << dib3->Get() << endl;
    cout << dib4->Get() << "\t" << dib5->Get() << endl;
    delete dib;
    delete dib2;
    delete dib3;
    delete dib4;
    delete dib5;

    //test shared_ptr
    class FOO
    {
    public:
       FOO(DRImpBase* base)
          :_base(base)
       {}

       ~FOO()
       {}

    private:
       std::shared_ptr<DRImpBase> _base;
    };

    std::shared_ptr<DRImpBase> base(new DRImpBase(8));
    std::shared_ptr<DRImpBase> base2(base);
    {
       FOO foo(base.get());
    }


    //test copy constructor
    TPoint1 M(12,20), P(0,0), S(0,0);
    TPoint1 N(M);
    P = fun(N);
    S = M;
    cout << "P=" << P.Xcoord() << "," << P.Ycoord() << endl;
    cout << "S=" << S.Xcoord() << "," << S.Ycoord() << endl;
    cout << endl;
    //运行结果
    //Copy contructor called : 执行语句TPoint1 N(M)时调用拷贝构造
    //Copy contructor called : 执行语句fun(N)实参初始化形参时候调用拷贝构造
    //ok
    //Copy contructor called : 执行语句return R后退出函数前创建临时变量时调用拷贝构造
    //Destructor called : 析构fun函数体内的R对象
    //Destructor called : 析构fun函数体内的Q对象
    //Copy operator called : 执行语句P = fun(N)临时对象被释放之前，将它的内容赋值给对象P
    //Destructor called : 析构fun函数临时对象
    //Copy operator called : 执行语句S = M
    //P=22,35
    //S=12,20
    //Destructor called : 析构N对象
    //Destructor called : 析构S对象
    //Destructor called : 析构P对象
    //Destructor called : 析构M对象

    TPoint1 M2(12,20), P2(0,0), S2(0,0);
    TPoint1 N2(M2);
    P2[fun(N2)];
    S2[M2];
    cout << "P2=" << P2.Xcoord() << "," << P2.Ycoord() << endl;
    cout << "S2=" << S2.Xcoord() << "," << S2.Ycoord() << endl;
    //运行结果
    //Copy contructor called : 执行语句TPoint1 N2(M2)时调用拷贝构造
    //Copy contructor called : 执行语句fun(N2)实参初始化形参时候调用拷贝构造
    //ok
    //Copy contructor called : 执行语句return R后退出函数前创建临时变量时调用拷贝构造
    //Destructor called : 析构fun函数体内的R对象
    //Destructor called : 析构fun函数体内的Q对象
    //Copy operator called : 执行语句P2[fun(N2)]临时对象被释放之前，将它的内容赋值给对象P2
    //Copy contructor called : 执行语句return *this后退出函数前创建临时变量时调用拷贝构造，因为这里返回不是引用
    //Destructor called : 析构fun函数临时对象
    //Destructor called : 析构operator[]临时对象
    //Copy operator called : 执行语句S2[M2]
    //Copy contructor called : 执行语句return *this后退出函数前创建临时变量时调用拷贝构造，因为这里返回不是引用
    //Destructor called : 析构operator[]临时对象
    //P=22,35
    //S=12,20
    //Destructor called : 析构N2对象
    //Destructor called : 析构S2对象
    //Destructor called : 析构P2对象
    //Destructor called : 析构M2对象
    //Destructor called : 析构N对象
    //Destructor called : 析构S对象
    //Destructor called : 析构P对象
    //Destructor called : 析构M对象

	_getch();
}

