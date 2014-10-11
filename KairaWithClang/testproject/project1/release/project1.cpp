/* This file is automatically generated
   do not edit this file directly! */

#include "project1.h"
void place_user_fn_103(ca::Context &ctx, ca::TokenList<int > &place);
void place_user_fn_106(ca::Context &ctx, ca::TokenList<int > &place);
class Vars_105 {
	public:
	Vars_105(ca::Context &ctx,int &y) : ctx(ctx),y(y) {
	}
	ca::Context &ctx;
	int &y;
};
void transition_user_fn_105(ca::Context &ctx, Vars_105 &var);
class Tokens_105  : public ca::Binding {
	public:
	Tokens_105() {};
	Tokens_105(const Tokens_105 &t) {
		if (t.token_1001 != NULL) {
			token_1001 = new ca::Token<int >(t.token_1001->value);
		} else {
			token_1001 = NULL;
		}
	}
	Tokens_105& operator=(const Tokens_105 &t) {
		if (this != &t) {
			if (t.token_1001 != NULL) {
				delete token_1001;
				token_1001 = new ca::Token<int >(t.token_1001->value);
			} else {
				token_1001 = NULL;
			}
		}
		return *this;
	}
	~Tokens_105() {
		if (token_1001 != NULL) {
			delete token_1001;
		}
	}
	ca::Binding* copy() {
		Tokens_105 *t = new Tokens_105(*this);
		return t;
	}
	ca::Token<int > *token_1001;
};
class Transition_105  : public ca::TransitionDef {
	public:
	Transition_105() : ca::TransitionDef(105, "test", ca::TRANSITION_NORMAL, 0) {
	}
	ca::FireResult full_fire(ca::ThreadBase *thread, ca::NetBase *net);
	ca::Binding* fire_phase1(ca::ThreadBase *thread, ca::NetBase *net);
	void fire_phase2(ca::ThreadBase *thread, ca::NetBase *net, ca::Binding *data);
	bool is_enable(ca::ThreadBase *thread, ca::NetBase *net);
};
static Transition_105 transition_105;

void place_user_fn_119(ca::Context &ctx, ca::TokenList<std::string > &place);
class Vars_120 {
	public:
	Vars_120(ca::Context &ctx,std::string &s) : ctx(ctx),s(s) {
	}
	ca::Context &ctx;
	std::string &s;
};
void transition_user_fn_120(ca::Context &ctx, Vars_120 &var);
class Tokens_120  : public ca::Binding {
	public:
	Tokens_120() {};
	Tokens_120(const Tokens_120 &t) {
		if (t.token_1005 != NULL) {
			token_1005 = new ca::Token<std::string >(t.token_1005->value);
		} else {
			token_1005 = NULL;
		}
	}
	Tokens_120& operator=(const Tokens_120 &t) {
		if (this != &t) {
			if (t.token_1005 != NULL) {
				delete token_1005;
				token_1005 = new ca::Token<std::string >(t.token_1005->value);
			} else {
				token_1005 = NULL;
			}
		}
		return *this;
	}
	~Tokens_120() {
		if (token_1005 != NULL) {
			delete token_1005;
		}
	}
	ca::Binding* copy() {
		Tokens_120 *t = new Tokens_120(*this);
		return t;
	}
	ca::Token<std::string > *token_1005;
};
class Transition_120  : public ca::TransitionDef {
	public:
	Transition_120() : ca::TransitionDef(120, "ss", ca::TRANSITION_NORMAL, 0) {
	}
	ca::FireResult full_fire(ca::ThreadBase *thread, ca::NetBase *net);
	ca::Binding* fire_phase1(ca::ThreadBase *thread, ca::NetBase *net);
	void fire_phase2(ca::ThreadBase *thread, ca::NetBase *net, ca::Binding *data);
	bool is_enable(ca::ThreadBase *thread, ca::NetBase *net);
};
static Transition_120 transition_120;

class Net_101  : public ca::Net {
	public:
	Net_101(ca::NetDef * def,ca::Thread * thread) : ca::Net(def, thread) {
	}
	ca::NetBase * copy() {
		Net_101 *net = new Net_101(*this);
		return net;
	}
	ca::Place<int > place_103;
	ca::Place<int > place_106;
	void write_reports_content(ca::ThreadBase *thread, ca::Output &output) {
		output.child("place");
		output.set("id", 103);
		{
			ca::Token<int > *t = place_103.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_103.begin());
			}
		}
		output.back();
		output.child("place");
		output.set("id", 106);
		{
			ca::Token<int > *t = place_106.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_106.begin());
			}
		}
		output.back();
	}
	void receive(ca::ThreadBase *__kaira__thread, int from_process, int place_pos, ca::Unpacker &unpacker) {
		switch(place_pos) {
		}
	}
};
class Net_118  : public ca::Net {
	public:
	Net_118(ca::NetDef * def,ca::Thread * thread) : ca::Net(def, thread) {
	}
	ca::NetBase * copy() {
		Net_118 *net = new Net_118(*this);
		return net;
	}
	ca::Place<std::string > place_119;
	ca::Place<std::string > place_122;
	void write_reports_content(ca::ThreadBase *thread, ca::Output &output) {
		output.child("place");
		output.set("id", 119);
		{
			ca::Token<std::string > *t = place_119.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_119.begin());
			}
		}
		output.back();
		output.child("place");
		output.set("id", 122);
		{
			ca::Token<std::string > *t = place_122.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_122.begin());
			}
		}
		output.back();
	}
	void receive(ca::ThreadBase *__kaira__thread, int from_process, int place_pos, ca::Unpacker &unpacker) {
		switch(place_pos) {
		}
	}
};
ca::NetBase * spawn_101(ca::ThreadBase *__kaira__thread, ca::NetDef *__kaira__def) {
	Net_101 *__kaira__net = new Net_101(__kaira__def, (ca::Thread*) __kaira__thread);
	ca::Context ctx(__kaira__thread, __kaira__net);
	int __kaira__pid = __kaira__thread->get_process_id();
	if (__kaira__pid == 0) {
		__kaira__net->place_103.add(0);
		{
			ca::TokenList<int > __kaira__list;
			place_user_fn_103(ctx, __kaira__list);
			__kaira__net->place_103.overtake(__kaira__list);
		}
	}
	if (__kaira__pid == 0) {
		__kaira__net->place_106.add(8);
		{
			ca::TokenList<int > __kaira__list;
			place_user_fn_106(ctx, __kaira__list);
			__kaira__net->place_106.overtake(__kaira__list);
		}
	}
	return __kaira__net;
}
ca::FireResult Transition_105::full_fire(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_106.size() < 1) return ca::NOT_ENABLED;
	// Inscription id=107 uid=1001 expr=y
	ca::Token < int > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_106.begin();
	int &y = __kaira__token_1001->value;
	if (!(y > 5)) {
		return ca::NOT_ENABLED;
	}
	{
		{
			__kaira__n->place_106.remove(__kaira__token_1001);
		}
		__kaira__n->activate_transition_by_pos_id(0);
		Vars_105 __kaira__vars(ctx,y);
		transition_user_fn_105(ctx, __kaira__vars);
		__kaira__n->place_103.add(y+5);
		delete __kaira__token_1001;
		return ca::TRANSITION_FIRED;
	}
	return ca::NOT_ENABLED;
}
ca::Binding* Transition_105::fire_phase1(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_106.size() < 1) return NULL;
	// Inscription id=107 uid=1001 expr=y
	ca::Token < int > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_106.begin();
	int &y = __kaira__token_1001->value;
	if (!(y > 5)) {
		return NULL;
	}
	{
		{
			__kaira__n->place_106.remove(__kaira__token_1001);
		}
		Tokens_105 *__kaira__tokens = new Tokens_105();
		__kaira__tokens->token_1001 = __kaira__token_1001;
		return __kaira__tokens;
	}
	return NULL;
}
void Transition_105::fire_phase2(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net, ca::Binding *__kaira__binding)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	Tokens_105 *__kaira__tokens = static_cast<Tokens_105*>(__kaira__binding);
	ca::Token<int > *__kaira__token_1001 = __kaira__tokens->token_1001;
	int &y = __kaira__token_1001->value;
	__kaira__n->activate_transition_by_pos_id(0);
	Vars_105 __kaira__vars(ctx,y);
	transition_user_fn_105(ctx, __kaira__vars);
	__kaira__n->place_103.add(y+5);
	delete __kaira__binding;
}
bool Transition_105::is_enable(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_106.size() < 1) return false;
	// Inscription id=107 uid=1001 expr=y
	ca::Token < int > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_106.begin();
	int &y = __kaira__token_1001->value;
	if (!(y > 5)) {
		return false;
	}
	{
		return true;
	}
	return false;
}
ca::NetBase * spawn_118(ca::ThreadBase *__kaira__thread, ca::NetDef *__kaira__def) {
	Net_118 *__kaira__net = new Net_118(__kaira__def, (ca::Thread*) __kaira__thread);
	ca::Context ctx(__kaira__thread, __kaira__net);
	int __kaira__pid = __kaira__thread->get_process_id();
	if (__kaira__pid == 0) {
		__kaira__net->place_119.add("de");
		{
			ca::TokenList<std::string > __kaira__list;
			place_user_fn_119(ctx, __kaira__list);
			__kaira__net->place_119.overtake(__kaira__list);
		}
	}
	return __kaira__net;
}
ca::FireResult Transition_120::full_fire(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_118 *__kaira__n = (Net_118*) __kaira__net;
	if (__kaira__n->place_119.size() < 1) return ca::NOT_ENABLED;
	// Inscription id=121 uid=1005 expr=s
	ca::Token < std::string > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_119.begin();
	std::string &s = __kaira__token_1005->value;
	{
		{
			__kaira__n->place_119.remove(__kaira__token_1005);
		}
		__kaira__n->activate_transition_by_pos_id(0);
		Vars_120 __kaira__vars(ctx,s);
		transition_user_fn_120(ctx, __kaira__vars);
		__kaira__n->place_122.add_token(__kaira__token_1005);
		return ca::TRANSITION_FIRED;
	}
	return ca::NOT_ENABLED;
}
ca::Binding* Transition_120::fire_phase1(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_118 *__kaira__n = (Net_118*) __kaira__net;
	if (__kaira__n->place_119.size() < 1) return NULL;
	// Inscription id=121 uid=1005 expr=s
	ca::Token < std::string > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_119.begin();
	std::string &s = __kaira__token_1005->value;
	{
		{
			__kaira__n->place_119.remove(__kaira__token_1005);
		}
		Tokens_120 *__kaira__tokens = new Tokens_120();
		__kaira__tokens->token_1005 = __kaira__token_1005;
		return __kaira__tokens;
	}
	return NULL;
}
void Transition_120::fire_phase2(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net, ca::Binding *__kaira__binding)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_118 *__kaira__n = (Net_118*) __kaira__net;
	Tokens_120 *__kaira__tokens = static_cast<Tokens_120*>(__kaira__binding);
	ca::Token<std::string > *__kaira__token_1005 = __kaira__tokens->token_1005;
	std::string &s = __kaira__token_1005->value;
	__kaira__n->activate_transition_by_pos_id(0);
	Vars_120 __kaira__vars(ctx,s);
	transition_user_fn_120(ctx, __kaira__vars);
	__kaira__n->place_122.add_token(__kaira__token_1005);
	__kaira__tokens->token_1005 = NULL;
	delete __kaira__binding;
}
bool Transition_120::is_enable(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_118 *__kaira__n = (Net_118*) __kaira__net;
	if (__kaira__n->place_119.size() < 1) return false;
	// Inscription id=121 uid=1005 expr=s
	ca::Token < std::string > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_119.begin();
	std::string &s = __kaira__token_1005->value;
	{
		return true;
	}
	return false;
}
int main(int argc, char **argv)
{
	ca::project_description("<project library-octave=\"False\" library-rpc=\"False\" target_env=\"C++\"><configuration><build-option name=\"LIBS\" /><build-option name=\"CFLAGS\">-O2</build-option><head-code>int testing;\ndouble aaaaaa;\nint AAA;\n\n\nvoid test()\n{\n\nAAA = 25;\n\n}</head-code></configuration><net id=\"101\" name=\"project1\"><place id=\"103\" label-x=\"-332\" label-y=\"-148\" name=\"x\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-332\" y=\"-148\"><place-type x=\"-315\" y=\"-131\">int</place-type><init x=\"-315\" y=\"-178\">[0]</init><code>\tAAA = 11;\n\tctx.quit();\n\tint abab;\n\tabab = 15;\n\t\n\tasdasdad\n\t\n\tabab += abab * abab + 15;\n</code><trace trace-tokens=\"False\" /></place><place id=\"106\" label-x=\"-842\" label-y=\"-151\" name=\"y\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-842\" y=\"-151\"><place-type x=\"-825\" y=\"-134\">int</place-type><init x=\"-825\" y=\"-181\">[8]</init><code>place.add(5);\ntesting = 15;\nplace.add_token(new ca::Token&lt;int&gt;());\n  int eeee = 99;\n  AAA = 15165;\n  \n  \n  \n</code><trace trace-tokens=\"False\" /></place><transition clock=\"False\" collective=\"False\" id=\"105\" label-x=\"-602\" label-y=\"-148\" name=\"test\" priority=\"\" sx=\"70\" sy=\"36\" x=\"-637\" y=\"-166\"><guard x=\"-623\" y=\"-185\">y &gt; 5</guard><code>\tvar.y = 15;\n\tint *poi;\n\ttesting = 9898;\n\tAAA = 99;\n</code></transition><edge from_item=\"106\" id=\"107\" to_item=\"105\"><inscription x=\"-728.0\" y=\"-149.0\">y</inscription></edge><edge from_item=\"105\" id=\"108\" to_item=\"103\"><inscription x=\"-458.0\" y=\"-147.0\">y+5</inscription></edge></net><net id=\"118\" name=\"pro2\"><place id=\"119\" label-x=\"-381\" label-y=\"-117\" name=\"te\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-381\" y=\"-117\"><place-type x=\"-364\" y=\"-100\">std::string</place-type><init x=\"-364\" y=\"-147\">[\"de\"]</init><code>\tplace.add(\"testing\");\n</code><trace trace-tokens=\"False\" /></place><place id=\"122\" label-x=\"-1\" label-y=\"-119\" name=\"\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-1\" y=\"-119\"><place-type x=\"16\" y=\"-102\">std::string</place-type><init x=\"16\" y=\"-149\" /><trace trace-tokens=\"False\" /></place><transition clock=\"False\" collective=\"False\" id=\"120\" label-x=\"-225\" label-y=\"-118\" name=\"ss\" priority=\"\" sx=\"70\" sy=\"36\" x=\"-260\" y=\"-136\"><guard x=\"-260\" y=\"-156\" /><code>\tvar.s += var.s;\n\t\n</code></transition><edge from_item=\"119\" id=\"121\" to_item=\"120\"><inscription x=\"-310.0\" y=\"-117.0\">s</inscription></edge><edge from_item=\"120\" id=\"123\" to_item=\"122\"><inscription x=\"-105.0\" y=\"-118.0\">s</inscription></edge></net></project>");
	std::vector<ca::Parameter*> parameters;

	ca::init(argc, argv, parameters, false);

	ca::NetDef *def_101 = new ca::NetDef(0, 101, spawn_101);
	def_101->register_transition(&transition_105);
	ca::NetDef *def_118 = new ca::NetDef(1, 118, spawn_118);
	def_118->register_transition(&transition_120);
	ca::NetDef *defs[] = {def_101,def_118};
	ca::setup(2, defs, true);
	ca::spawn_net(0);
	ca::main();
	return 0;
}
#line 1 "*105/function"
void transition_user_fn_105(ca::Context &ctx, Vars_105 &var)
{
	var.y = 15;
	int *poi;
	testing = 9898;
	AAA = 99;
}
#line 1 "*103/init_function"
void place_user_fn_103(ca::Context &ctx, ca::TokenList<int > &place)
{
	AAA = 11;
	ctx.quit();
	int abab;
	abab = 15;
	
	asdasdad
	
	abab += abab * abab + 15;
}
#line 1 "*106/init_function"
void place_user_fn_106(ca::Context &ctx, ca::TokenList<int > &place)
{
place.add(5);
testing = 15;
place.add_token(new ca::Token<int>());
  int eeee = 99;
  AAA = 15165;
  
  
  
}
#line 1 "*120/function"
void transition_user_fn_120(ca::Context &ctx, Vars_120 &var)
{
	var.s += var.s;
	
}
#line 1 "*119/init_function"
void place_user_fn_119(ca::Context &ctx, ca::TokenList<std::string > &place)
{
	place.add("testing");
}