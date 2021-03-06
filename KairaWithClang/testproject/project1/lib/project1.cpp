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

class Vars_112 {
	public:
	Vars_112(ca::Context &ctx,myvar &v) : ctx(ctx),v(v) {
	}
	ca::Context &ctx;
	myvar &v;
};
void transition_user_fn_112(ca::Context &ctx, Vars_112 &var);
class Tokens_112  : public ca::Binding {
	public:
	Tokens_112() {};
	Tokens_112(const Tokens_112 &t) {
		if (t.token_1005 != NULL) {
			token_1005 = new ca::Token<myvar >(t.token_1005->value);
		} else {
			token_1005 = NULL;
		}
	}
	Tokens_112& operator=(const Tokens_112 &t) {
		if (this != &t) {
			if (t.token_1005 != NULL) {
				delete token_1005;
				token_1005 = new ca::Token<myvar >(t.token_1005->value);
			} else {
				token_1005 = NULL;
			}
		}
		return *this;
	}
	~Tokens_112() {
		if (token_1005 != NULL) {
			delete token_1005;
		}
	}
	ca::Binding* copy() {
		Tokens_112 *t = new Tokens_112(*this);
		return t;
	}
	ca::Token<myvar > *token_1005;
};
class Transition_112  : public ca::TransitionDef {
	public:
	Transition_112() : ca::TransitionDef(112, "none", ca::TRANSITION_NORMAL, 0) {
	}
	ca::FireResult full_fire(ca::ThreadBase *thread, ca::NetBase *net);
	ca::Binding* fire_phase1(ca::ThreadBase *thread, ca::NetBase *net);
	void fire_phase2(ca::ThreadBase *thread, ca::NetBase *net, ca::Binding *data);
	bool is_enable(ca::ThreadBase *thread, ca::NetBase *net);
};
static Transition_112 transition_112;

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
	ca::Place<myvar > place_110;
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
		output.child("place");
		output.set("id", 110);
		{
			ca::Token<myvar > *t = place_110.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_110.begin());
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
	if (__kaira__pid == 0) {
		__kaira__net->place_110.add(glob);
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
ca::FireResult Transition_112::full_fire(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_110.size() < 1) return ca::NOT_ENABLED;
	// Inscription id=113 uid=1005 expr=v
	ca::Token < myvar > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_110.begin();
	myvar &v = __kaira__token_1005->value;
	{
		{
			__kaira__n->place_110.remove(__kaira__token_1005);
		}
		__kaira__n->activate_transition_by_pos_id(1);
		Vars_112 __kaira__vars(ctx,v);
		transition_user_fn_112(ctx, __kaira__vars);
		delete __kaira__token_1005;
		return ca::TRANSITION_FIRED;
	}
	return ca::NOT_ENABLED;
}
ca::Binding* Transition_112::fire_phase1(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_110.size() < 1) return NULL;
	// Inscription id=113 uid=1005 expr=v
	ca::Token < myvar > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_110.begin();
	myvar &v = __kaira__token_1005->value;
	{
		{
			__kaira__n->place_110.remove(__kaira__token_1005);
		}
		Tokens_112 *__kaira__tokens = new Tokens_112();
		__kaira__tokens->token_1005 = __kaira__token_1005;
		return __kaira__tokens;
	}
	return NULL;
}
void Transition_112::fire_phase2(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net, ca::Binding *__kaira__binding)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	Tokens_112 *__kaira__tokens = static_cast<Tokens_112*>(__kaira__binding);
	ca::Token<myvar > *__kaira__token_1005 = __kaira__tokens->token_1005;
	myvar &v = __kaira__token_1005->value;
	__kaira__n->activate_transition_by_pos_id(1);
	Vars_112 __kaira__vars(ctx,v);
	transition_user_fn_112(ctx, __kaira__vars);
	delete __kaira__binding;
}
bool Transition_112::is_enable(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_110.size() < 1) return false;
	// Inscription id=113 uid=1005 expr=v
	ca::Token < myvar > *__kaira__token_1005;
	__kaira__token_1005 = __kaira__n->place_110.begin();
	myvar &v = __kaira__token_1005->value;
	{
		return true;
	}
	return false;
}
void project1()
{
	ca::spawn_net(0);
	Net_101 *__kaira__n = (Net_101*)ca::get_main_net();
	__kaira__n->set_manual_delete();
	ca::main();
	delete __kaira__n;
}
void calib_init(int argc, char **argv)
{
	ca::project_description("<project library-octave=\"False\" library-rpc=\"False\" target_env=\"C++\"><configuration><build-option name=\"LIBS\" /><build-option name=\"CFLAGS\">-O2</build-option><head-code>\n\nint abc;\ndouble aaaaaa;\nint AAA;\nstruct tt\n{\ntt()\n{\n\n}\n\n};\n\nclass myvar\n{\npublic:\nmyvar()\n{\n\n}\nstd::string token_name() const\n{\nreturn \"myvar\";\n}\nchar * test()\n{\n\nreturn (char*)\"aloha\";\n}\n};\n\nmyvar glob;\n</head-code></configuration><net id=\"101\" name=\"project1\"><place id=\"103\" label-x=\"-332.0\" label-y=\"-148.0\" name=\"x\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-332.0\" y=\"-148.0\"><place-type x=\"-315.0\" y=\"-131.0\">int</place-type><init x=\"-315.0\" y=\"-178.0\">[0]</init><code>\t\n\tctx.quit();\n</code><trace trace-tokens=\"False\" /></place><place id=\"106\" label-x=\"-844.0\" label-y=\"-151.0\" name=\"y\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-844.0\" y=\"-151.0\"><place-type x=\"-827.0\" y=\"-134.0\">int</place-type><init x=\"-827.0\" y=\"-181.0\">[8]</init><code>place.add(5);\nint abc;\nplace.add_token(new ca::Token&lt;int&gt;());\n\t\n</code><trace trace-tokens=\"False\" /></place><place id=\"110\" label-x=\"-770\" label-y=\"85\" name=\"var\" radius=\"20\" sx=\"0\" sy=\"0\" x=\"-770\" y=\"85\"><place-type x=\"-753\" y=\"102\">myvar</place-type><init x=\"-753\" y=\"55\">[glob]</init><trace trace-tokens=\"False\" /></place><transition clock=\"False\" collective=\"False\" id=\"105\" label-x=\"-602.0\" label-y=\"-148.0\" name=\"test\" priority=\"\" sx=\"70\" sy=\"36\" x=\"-637.0\" y=\"-166.0\"><guard x=\"-623.0\" y=\"-185.0\">y &gt; 5</guard><code>\tvar.y = 15;\n\t\n</code></transition><transition clock=\"False\" collective=\"False\" id=\"112\" label-x=\"-592\" label-y=\"88\" name=\"none\" priority=\"\" sx=\"70\" sy=\"36\" x=\"-627\" y=\"70\"><guard x=\"-627\" y=\"50\" /><code>\tprintf(var.v.test());\n\tctx.quit();\n\t\n\t\n\t\n\t\n\t\n\t\n</code></transition><edge from_item=\"106\" id=\"107\" to_item=\"105\"><inscription x=\"-729.173799212\" y=\"-149.548320335\">y</inscription></edge><edge from_item=\"105\" id=\"108\" to_item=\"103\"><inscription x=\"-458.732102013\" y=\"-147.093863722\">y+5</inscription></edge><edge from_item=\"110\" id=\"113\" to_item=\"112\"><inscription x=\"-688.0\" y=\"86.0\">v</inscription></edge></net></project>");
	std::vector<ca::Parameter*> parameters;

	ca::init(argc, argv, parameters, false);

	ca::NetDef *def_101 = new ca::NetDef(0, 101, spawn_101);
	def_101->register_transition(&transition_105);
	def_101->register_transition(&transition_112);
	ca::NetDef *defs[] = {def_101};
	ca::setup(1, defs, true);
}
#line 1 "*105/function"
void transition_user_fn_105(ca::Context &ctx, Vars_105 &var)
{
	var.y = 15;
	
}
#line 1 "*112/function"
void transition_user_fn_112(ca::Context &ctx, Vars_112 &var)
{
	printf(var.v.test());
	ctx.quit();
	
	
	
	
	
	
}
#line 1 "*103/init_function"
void place_user_fn_103(ca::Context &ctx, ca::TokenList<int > &place)
{
	
	ctx.quit();
}
#line 1 "*106/init_function"
void place_user_fn_106(ca::Context &ctx, ca::TokenList<int > &place)
{
place.add(5);
int abc;
place.add_token(new ca::Token<int>());
	
}
