#include <iostream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


using namespace std;

int main()
{
    CppUnit::TextUi::TestRunner runner;
    //��ע���TestSuite�л�ȡ�ض���TestSuite, û�в�����ȡδ������TestSuite
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("alltest");
    //������TestSuite��TestRunner��
    runner.addTest( registry.makeTest() );
    //���в���
    runner.run();

    cout << "Hello world!" << endl;

    return 0;
}
