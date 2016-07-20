/*As currently the checkformat script is essentially a string comparison, the test code does not need to compile*/

/*Indentation should be 2 spaces. Indented by scope except for namespaces and access modifiers*/
namespace foo {
class Foo {
public:
  Foo();
  ~Foo();

private:
  int m_bar;
  int m_foo;
};
}

/*Indent twice for member initialiser lists*/
Foo::Foo() : m_bar(1), m_foo(1) {
  // ctor body
}

/*Opening curly braces should be placed in the same line; Closing curly braces should be in a new line.*/
class Foo() {
  // my class definition
};

if (condition) {
  // doSomething
  int x;
}

if (condition) {
  // doSomething
} else {
  // doSomethingElse
}

for (int a = 10; a < 20; ++a) {
  // doSomethingRepeatedly
}

/*Example code*/
#include "OtherClass.h"

/** @class foo::MyClass MyPackage/MyPackage/MyClass.h MyClass.h
 *
 *  Short description of what your class does
 *
 *  @author Main Author
 *  @author Other Contributor
 *  @date yyyy-mm-dd
 */
namespace foo {
class MyClass : public OtherClass {
public:
  /** @enum foo::MyEnum
   *  Description of the enum
   */
  enum class MyEnum { kVal1, kVal2 };

  /// Description about ctor
  MyClass(int a, int b);

  /** doSomething: does something
    * @param[in] f is used to do...
    * @returns an integer
    */
  int doSomething(const float& f);

private:
  int m_a;  ///< short member a documentation
  /// a rather long description for member b that needs a whole line
  int m_b
};
}