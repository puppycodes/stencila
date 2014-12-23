#include <boost/test/unit_test.hpp>

#include <stencila/stencil.hpp>
using namespace Stencila;

BOOST_AUTO_TEST_SUITE(stencil_directives)


BOOST_AUTO_TEST_CASE(exec){
	typedef Stencil::Execute E;
	{
		E e("py");
		BOOST_CHECK_EQUAL(e.contexts.size(),1);
		BOOST_CHECK_EQUAL(e.contexts[0],"py");
	}{
		E e("r,py");
		BOOST_CHECK_EQUAL(e.contexts.size(),2);
		BOOST_CHECK_EQUAL(e.contexts[0],"r");
		BOOST_CHECK_EQUAL(e.contexts[1],"py");
	}{
		E e("r,   py");
		BOOST_CHECK_EQUAL(e.contexts.size(),2);
		BOOST_CHECK_EQUAL(e.contexts[0],"r");
		BOOST_CHECK_EQUAL(e.contexts[1],"py");
	}{
		try {
			E e("r,bf");
		} catch(const Stencil::DirectiveException& exc){
			BOOST_CHECK_EQUAL(exc.type,"context-invalid");
		}  
	}

	{
		E e("r format text");
		BOOST_CHECK_EQUAL(e.format,"text");
	}{
		E e("r format png");
		BOOST_CHECK_EQUAL(e.format,"png");
	}{
		E e("r format svg");
		BOOST_CHECK_EQUAL(e.format,"svg");
	}{
		try {
			E e("r format gnp");
		} catch(const Stencil::DirectiveException& exc){
			BOOST_CHECK_EQUAL(exc.type,"format-invalid");
		}  
	}

	{
		E e("r format png width 19");
		BOOST_CHECK_EQUAL(e.width,"19");
		BOOST_CHECK_EQUAL(e.height,"17");
		BOOST_CHECK_EQUAL(e.units,"cm");
	}

	{
		E e("py,r format png width 10 units cm size 4.2x8.4in");
		BOOST_CHECK_EQUAL(e.contexts.size(),2);
		BOOST_CHECK_EQUAL(e.contexts[0],"py");
		BOOST_CHECK_EQUAL(e.contexts[1],"r");
		BOOST_CHECK_EQUAL(e.format,"png");
		BOOST_CHECK_EQUAL(e.size,"4.2x8.4in");
		BOOST_CHECK_EQUAL(e.width,"4.2");
		BOOST_CHECK_EQUAL(e.height,"8.4");
		BOOST_CHECK_EQUAL(e.units,"in");
	}{
		try {
			E e("r format png size 10x10km");
		} catch(const Stencil::DirectiveException& exc){
			BOOST_CHECK_EQUAL(exc.type,"units-invalid");
			BOOST_CHECK_EQUAL(exc.data,"km");
		}
	}

	{
		E e("r");
		BOOST_CHECK(not e.constant);
	}
	{
		E e("r const");
		BOOST_CHECK(e.constant);
	}

	{
		E e("cila");
		BOOST_CHECK(not e.show);
	}
	{
		E e("cila show");
		BOOST_CHECK(e.show);
	}

}

BOOST_AUTO_TEST_CASE(par){
	typedef Stencil::Parameter P;
	{
		P p("x");
		BOOST_CHECK_EQUAL(p.name,"x");
		BOOST_CHECK_EQUAL(p.type,"");
		BOOST_CHECK_EQUAL(p.value,"");
	}{
		P p("x type number");
		BOOST_CHECK_EQUAL(p.name,"x");
		BOOST_CHECK_EQUAL(p.type,"number");
		BOOST_CHECK_EQUAL(p.value,"");
	}{
		P p("x type number value 42");
		BOOST_CHECK_EQUAL(p.name,"x");
		BOOST_CHECK_EQUAL(p.type,"number");
		BOOST_CHECK_EQUAL(p.value,"42");
	}{
		P p("x value 42");
		BOOST_CHECK_EQUAL(p.name,"x");
		BOOST_CHECK_EQUAL(p.type,"");
		BOOST_CHECK_EQUAL(p.value,"42");
	}{
		P p("x value pi*7*6");
		BOOST_CHECK_EQUAL(p.name,"x");
		BOOST_CHECK_EQUAL(p.type,"");
		BOOST_CHECK_EQUAL(p.value,"pi*7*6");
	}{
		try{
			P p("x foo bar");
		} catch(const Stencil::DirectiveException& exc){
			BOOST_CHECK_EQUAL(exc.type,"syntax");
		}
	}
}

BOOST_AUTO_TEST_CASE(includ){
	typedef Stencil::Include I;
	{
		I i("x");
		BOOST_CHECK_EQUAL(i.address,"x");
		BOOST_CHECK_EQUAL(i.address_eval,false);
		BOOST_CHECK_EQUAL(i.select,"");
	}{
		I i("x select y");
		BOOST_CHECK_EQUAL(i.address,"x");
		BOOST_CHECK_EQUAL(i.select,"y");
		BOOST_CHECK_EQUAL(i.select_eval,false);
	}{
		I i(". select #id .class");
		BOOST_CHECK_EQUAL(i.address,".");
		BOOST_CHECK_EQUAL(i.select,"#id .class");
	}{
		I i("eval x+'stencil'");
		BOOST_CHECK_EQUAL(i.address,"x+'stencil'");
		BOOST_CHECK_EQUAL(i.address_eval,true);
	}{
		I i("eval 'address'+'/'+'of/stencil' select eval '#macro-id'");
		BOOST_CHECK_EQUAL(i.address,"'address'+'/'+'of/stencil'");
		BOOST_CHECK_EQUAL(i.address_eval,true);
		BOOST_CHECK_EQUAL(i.select,"'#macro-id'");
		BOOST_CHECK_EQUAL(i.select_eval,true);
	}
}

BOOST_AUTO_TEST_SUITE_END()
