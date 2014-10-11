/* This file is automatically generated
   do not edit this file directly! */

#include "sieve.h"
ca::ParameterInt param::N("N", "", ca::PARAMETER_MANDATORY);
void place_user_fn_102(ca::Context &ctx, ca::TokenList<Segment > &place);
class Vars_103 {
	public:
	Vars_103(ca::Context &ctx,int &next_num,int &num,int &prime,Segment &segment,std::vector<int > &targets) : ctx(ctx),next_num(next_num),num(num),prime(prime),segment(segment),targets(targets) {
	}
	ca::Context &ctx;
	int &next_num;
	int &num;
	int &prime;
	Segment &segment;
	std::vector<int > &targets;
};
void transition_user_fn_103(ca::Context &ctx, Vars_103 &var);
class Tokens_103  : public ca::Binding {
	public:
	Tokens_103() {};
	Tokens_103(const Tokens_103 &t) {
		if (t.token_1001 != NULL) {
			token_1001 = new ca::Token<Segment >(t.token_1001->value);
		} else {
			token_1001 = NULL;
		}
		if (t.token_1003 != NULL) {
			token_1003 = new ca::Token<int >(t.token_1003->value);
		} else {
			token_1003 = NULL;
		}
	}
	Tokens_103& operator=(const Tokens_103 &t) {
		if (this != &t) {
			if (t.token_1001 != NULL) {
				delete token_1001;
				token_1001 = new ca::Token<Segment >(t.token_1001->value);
			} else {
				token_1001 = NULL;
			}
			if (t.token_1003 != NULL) {
				delete token_1003;
				token_1003 = new ca::Token<int >(t.token_1003->value);
			} else {
				token_1003 = NULL;
			}
		}
		return *this;
	}
	~Tokens_103() {
		if (token_1001 != NULL) {
			delete token_1001;
		}
		if (token_1003 != NULL) {
			delete token_1003;
		}
	}
	ca::Binding* copy() {
		Tokens_103 *t = new Tokens_103(*this);
		return t;
	}
	ca::Token<Segment > *token_1001;
	ca::Token<int > *token_1003;
};
class Transition_103  : public ca::TransitionDef {
	public:
	Transition_103() : ca::TransitionDef(103, "Find\nprime", ca::TRANSITION_NORMAL, 0) {
	}
	ca::FireResult full_fire(ca::ThreadBase *thread, ca::NetBase *net);
	ca::Binding* fire_phase1(ca::ThreadBase *thread, ca::NetBase *net);
	void fire_phase2(ca::ThreadBase *thread, ca::NetBase *net, ca::Binding *data);
	bool is_enable(ca::ThreadBase *thread, ca::NetBase *net);
};
static Transition_103 transition_103;

class Vars_111 {
	public:
	Vars_111(ca::Context &ctx,int &prime,Segment &segment,ca::TokenList<int > &start) : ctx(ctx),prime(prime),segment(segment),start(start) {
	}
	ca::Context &ctx;
	int &prime;
	Segment &segment;
	ca::TokenList<int > &start;
};
void transition_user_fn_111(ca::Context &ctx, Vars_111 &var);
class Tokens_111  : public ca::Binding {
	public:
	Tokens_111() {};
	Tokens_111(const Tokens_111 &t) {
		if (t.token_1011 != NULL) {
			token_1011 = new ca::Token<int >(t.token_1011->value);
		} else {
			token_1011 = NULL;
		}
		if (t.token_1015 != NULL) {
			token_1015 = new ca::Token<Segment >(t.token_1015->value);
		} else {
			token_1015 = NULL;
		}
		tokens_1014 = t.tokens_1014;
	}
	Tokens_111& operator=(const Tokens_111 &t) {
		if (this != &t) {
			if (t.token_1011 != NULL) {
				delete token_1011;
				token_1011 = new ca::Token<int >(t.token_1011->value);
			} else {
				token_1011 = NULL;
			}
			if (t.token_1015 != NULL) {
				delete token_1015;
				token_1015 = new ca::Token<Segment >(t.token_1015->value);
			} else {
				token_1015 = NULL;
			}
			tokens_1014 = t.tokens_1014;
		}
		return *this;
	}
	~Tokens_111() {
		if (token_1011 != NULL) {
			delete token_1011;
		}
		if (token_1015 != NULL) {
			delete token_1015;
		}
	}
	ca::Binding* copy() {
		Tokens_111 *t = new Tokens_111(*this);
		return t;
	}
	ca::Token<int > *token_1011;
	ca::Token<Segment > *token_1015;
	ca::Place<int > tokens_1014;
};
class Transition_111  : public ca::TransitionDef {
	public:
	Transition_111() : ca::TransitionDef(111, "Mark\ncomposites", ca::TRANSITION_NORMAL, 0) {
	}
	ca::FireResult full_fire(ca::ThreadBase *thread, ca::NetBase *net);
	ca::Binding* fire_phase1(ca::ThreadBase *thread, ca::NetBase *net);
	void fire_phase2(ca::ThreadBase *thread, ca::NetBase *net, ca::Binding *data);
	bool is_enable(ca::ThreadBase *thread, ca::NetBase *net);
};
static Transition_111 transition_111;

class Net_101  : public ca::Net {
	public:
	Net_101(ca::NetDef * def,ca::Thread * thread) : ca::Net(def, thread) {
	}
	ca::NetBase * copy() {
		Net_101 *net = new Net_101(*this);
		return net;
	}
	ca::Place<Segment > place_102;
	ca::Place<int > place_104;
	ca::Place<int > place_107;
	ca::Place<int > place_109;
	void write_reports_content(ca::ThreadBase *thread, ca::Output &output) {
		output.child("place");
		output.set("id", 102);
		{
			ca::Token<Segment > *t = place_102.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_102.begin());
			}
		}
		output.back();
		output.child("place");
		output.set("id", 104);
		{
			ca::Token<int > *t = place_104.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_104.begin());
			}
		}
		output.back();
		output.child("place");
		output.set("id", 107);
		{
			ca::Token<int > *t = place_107.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_107.begin());
			}
		}
		output.back();
		output.child("place");
		output.set("id", 109);
		{
			ca::Token<int > *t = place_109.begin();
			if (t) {
				do {
					output.child("token");
					output.set("value", ca::token_name(t->value));
					output.back();
					t = t->next;
				} while (t != place_109.begin());
			}
		}
		output.back();
	}
	void receive(ca::ThreadBase *__kaira__thread, int from_process, int place_pos, ca::Unpacker &unpacker) {
		switch(place_pos) {
		case 110:
		{
			ca::Token<int > *token = new ca::Token<int >();
			ca::unpack(unpacker, token->value);
			this->place_109.add_token(token);
			this->activate_transition_by_pos_id(1);
		}
		break;
		}
	}
};
ca::NetBase * spawn_101(ca::ThreadBase *__kaira__thread, ca::NetDef *__kaira__def) {
	Net_101 *__kaira__net = new Net_101(__kaira__def, (ca::Thread*) __kaira__thread);
	ca::Context ctx(__kaira__thread, __kaira__net);
	int __kaira__pid = __kaira__thread->get_process_id();
	std::vector<int> __kaira__area_118 = all_processes(ctx);
	if (std::find(__kaira__area_118.begin(), __kaira__area_118.end(), __kaira__pid) != __kaira__area_118.end()) {
		{
			ca::TokenList<Segment > __kaira__list;
			place_user_fn_102(ctx, __kaira__list);
			__kaira__net->place_102.overtake(__kaira__list);
		}
	}
	if (__kaira__pid == 0) {
		__kaira__net->place_104.add(2);
	}
	return __kaira__net;
}
ca::FireResult Transition_103::full_fire(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_102.size() < 1) return ca::NOT_ENABLED;
	if (__kaira__n->place_104.size() < 1) return ca::NOT_ENABLED;
	// Inscription id=106 uid=1001 expr=segment
	ca::Token < Segment > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1001->value;
	// Inscription id=106 uid=1003 expr=num
	ca::Token < int > *__kaira__token_1003;
	__kaira__token_1003 = __kaira__n->place_104.begin();
	int &num = __kaira__token_1003->value;
	{
		{
			__kaira__n->place_102.remove(__kaira__token_1001);
			__kaira__n->place_104.remove(__kaira__token_1003);
		}
		__kaira__n->activate_transition_by_pos_id(0);
		ca::Token <int > *__kaira__token_1005 = new ca::Token<int >;
		int prime; // Fresh variable
		std::vector<int > targets; // Fresh variable
		int &next_num = __kaira__token_1005->value;
		Vars_103 __kaira__vars(ctx,next_num,num,prime,segment,targets);
		transition_user_fn_103(ctx, __kaira__vars);
		{
			ca::Packer __kaira__packer(ca::PACKER_DEFAULT_SIZE, ca::RESERVED_PREFIX);
			ca::pack(__kaira__packer, (prime));
			__kaira__thread->send_multicast(targets, __kaira__n, 110, 1, __kaira__packer);
		}
		__kaira__n->place_102.add_token(__kaira__token_1001);
		__kaira__n->activate_transition_by_pos_id(0);
		__kaira__n->activate_transition_by_pos_id(1);
		bool __kaira__token_1005_used = true;
		if (next_num > 0) {
			__kaira__n->place_107.add_token(__kaira__token_1005);
			__kaira__n->activate_transition_by_pos_id(1);
		} else {
			__kaira__token_1005_used = false;
		}
		delete __kaira__token_1003;
		if (!__kaira__token_1005_used) {
			delete __kaira__token_1005;
		}
		return ca::TRANSITION_FIRED;
	}
	return ca::NOT_ENABLED;
}
ca::Binding* Transition_103::fire_phase1(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_102.size() < 1) return NULL;
	if (__kaira__n->place_104.size() < 1) return NULL;
	// Inscription id=106 uid=1001 expr=segment
	ca::Token < Segment > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1001->value;
	// Inscription id=106 uid=1003 expr=num
	ca::Token < int > *__kaira__token_1003;
	__kaira__token_1003 = __kaira__n->place_104.begin();
	int &num = __kaira__token_1003->value;
	{
		{
			__kaira__n->place_102.remove(__kaira__token_1001);
			__kaira__n->place_104.remove(__kaira__token_1003);
		}
		Tokens_103 *__kaira__tokens = new Tokens_103();
		__kaira__tokens->token_1001 = __kaira__token_1001;
		__kaira__tokens->token_1003 = __kaira__token_1003;
		return __kaira__tokens;
	}
	return NULL;
}
void Transition_103::fire_phase2(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net, ca::Binding *__kaira__binding)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	Tokens_103 *__kaira__tokens = static_cast<Tokens_103*>(__kaira__binding);
	ca::Token<Segment > *__kaira__token_1001 = __kaira__tokens->token_1001;
	ca::Token<int > *__kaira__token_1003 = __kaira__tokens->token_1003;
	int &num = __kaira__token_1003->value;
	Segment &segment = __kaira__token_1001->value;
	__kaira__n->activate_transition_by_pos_id(0);
	ca::Token <int > *__kaira__token_1005 = new ca::Token<int >;
	int prime; // Fresh variable
	std::vector<int > targets; // Fresh variable
	int &next_num = __kaira__token_1005->value;
	Vars_103 __kaira__vars(ctx,next_num,num,prime,segment,targets);
	transition_user_fn_103(ctx, __kaira__vars);
	{
		ca::Packer __kaira__packer(ca::PACKER_DEFAULT_SIZE, ca::RESERVED_PREFIX);
		ca::pack(__kaira__packer, (prime));
		__kaira__thread->send_multicast(targets, __kaira__n, 110, 1, __kaira__packer);
	}
	__kaira__n->place_102.add_token(__kaira__token_1001);
	__kaira__n->activate_transition_by_pos_id(0);
	__kaira__n->activate_transition_by_pos_id(1);
	bool __kaira__token_1005_used = true;
	if (next_num > 0) {
		__kaira__n->place_107.add_token(__kaira__token_1005);
		__kaira__n->activate_transition_by_pos_id(1);
	} else {
		__kaira__token_1005_used = false;
	}
	__kaira__tokens->token_1001 = NULL;
	if (!__kaira__token_1005_used) {
		delete __kaira__token_1005;
	}
	delete __kaira__binding;
}
bool Transition_103::is_enable(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_102.size() < 1) return false;
	if (__kaira__n->place_104.size() < 1) return false;
	// Inscription id=106 uid=1001 expr=segment
	ca::Token < Segment > *__kaira__token_1001;
	__kaira__token_1001 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1001->value;
	// Inscription id=106 uid=1003 expr=num
	ca::Token < int > *__kaira__token_1003;
	__kaira__token_1003 = __kaira__n->place_104.begin();
	int &num = __kaira__token_1003->value;
	{
		return true;
	}
	return false;
}
ca::FireResult Transition_111::full_fire(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_109.size() < 1) return ca::NOT_ENABLED;
	if (__kaira__n->place_102.size() < 1) return ca::NOT_ENABLED;
	// Inscription id=116 uid=1011 expr=prime
	ca::Token < int > *__kaira__token_1011;
	__kaira__token_1011 = __kaira__n->place_109.begin();
	int &prime = __kaira__token_1011->value;
	// Inscription id=116 uid=1015 expr=segment
	ca::Token < Segment > *__kaira__token_1015;
	__kaira__token_1015 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1015->value;
	{
		{
			__kaira__n->place_109.remove(__kaira__token_1011);
			__kaira__n->place_102.remove(__kaira__token_1015);
		}
		__kaira__n->activate_transition_by_pos_id(1);
		ca::TokenList<int > start;
		__kaira__n->place_107.put_into(start);
		Vars_111 __kaira__vars(ctx,prime,segment,start);
		transition_user_fn_111(ctx, __kaira__vars);
		__kaira__n->place_104.overtake(start);
		__kaira__n->activate_transition_by_pos_id(0);
		__kaira__n->place_102.add_token(__kaira__token_1015);
		__kaira__n->activate_transition_by_pos_id(0);
		__kaira__n->activate_transition_by_pos_id(1);
		delete __kaira__token_1011;
		return ca::TRANSITION_FIRED;
	}
	return ca::NOT_ENABLED;
}
ca::Binding* Transition_111::fire_phase1(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_109.size() < 1) return NULL;
	if (__kaira__n->place_102.size() < 1) return NULL;
	// Inscription id=116 uid=1011 expr=prime
	ca::Token < int > *__kaira__token_1011;
	__kaira__token_1011 = __kaira__n->place_109.begin();
	int &prime = __kaira__token_1011->value;
	// Inscription id=116 uid=1015 expr=segment
	ca::Token < Segment > *__kaira__token_1015;
	__kaira__token_1015 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1015->value;
	{
		{
			__kaira__n->place_109.remove(__kaira__token_1011);
			__kaira__n->place_102.remove(__kaira__token_1015);
		}
		Tokens_111 *__kaira__tokens = new Tokens_111();
		__kaira__tokens->token_1011 = __kaira__token_1011;
		__kaira__tokens->token_1015 = __kaira__token_1015;
		__kaira__tokens->tokens_1014.overtake(__kaira__n->place_107);
		return __kaira__tokens;
	}
	return NULL;
}
void Transition_111::fire_phase2(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net, ca::Binding *__kaira__binding)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	Tokens_111 *__kaira__tokens = static_cast<Tokens_111*>(__kaira__binding);
	ca::Token<int > *__kaira__token_1011 = __kaira__tokens->token_1011;
	ca::Token<Segment > *__kaira__token_1015 = __kaira__tokens->token_1015;
	int &prime = __kaira__token_1011->value;
	Segment &segment = __kaira__token_1015->value;
	__kaira__n->activate_transition_by_pos_id(1);
	ca::TokenList<int > start;
	__kaira__tokens->tokens_1014.put_into(start);
	Vars_111 __kaira__vars(ctx,prime,segment,start);
	transition_user_fn_111(ctx, __kaira__vars);
	__kaira__n->place_104.overtake(start);
	__kaira__n->activate_transition_by_pos_id(0);
	__kaira__n->place_102.add_token(__kaira__token_1015);
	__kaira__n->activate_transition_by_pos_id(0);
	__kaira__n->activate_transition_by_pos_id(1);
	__kaira__tokens->token_1015 = NULL;
	delete __kaira__binding;
}
bool Transition_111::is_enable(ca::ThreadBase *__kaira__thread, ca::NetBase *__kaira__net)
{
	ca::Context ctx(__kaira__thread, __kaira__net);
	Net_101 *__kaira__n = (Net_101*) __kaira__net;
	if (__kaira__n->place_109.size() < 1) return false;
	if (__kaira__n->place_102.size() < 1) return false;
	// Inscription id=116 uid=1011 expr=prime
	ca::Token < int > *__kaira__token_1011;
	__kaira__token_1011 = __kaira__n->place_109.begin();
	int &prime = __kaira__token_1011->value;
	// Inscription id=116 uid=1015 expr=segment
	ca::Token < Segment > *__kaira__token_1015;
	__kaira__token_1015 = __kaira__n->place_102.begin();
	Segment &segment = __kaira__token_1015->value;
	{
		return true;
	}
	return false;
}
int main(int argc, char **argv)
{
	ca::project_description("<project library-octave=\"False\" library-rpc=\"False\" target_env=\"C++\"><configuration><parameter default=\"100\" description=\"\" name=\"N\" policy=\"mandatory\" type=\"int\" /><build-option name=\"LIBS\" /><build-option name=\"CFLAGS\">-O0 -ggdb</build-option><head-code>\nstruct Segment{\n\tstd::vector&lt;bool&gt; marks;\n\tint start;\n};\n\n\nnamespace ca {\n\t\n\tCA_TOKEN_NAME(Segment, segment) {\n\t\tstd::stringstream s;\n\t\ts &lt;&lt; \"[\" &lt;&lt; segment.start &lt;&lt; \",\" &lt;&lt; segment.start + segment.marks.size() - 1 &lt;&lt; \"]\";\n\t\tfor (int i = 0; i &lt; segment.marks.size(); i++) {\n\t\t\tif (segment.marks[i]) {\n\t\t\t\ts &lt;&lt; \" \" &lt;&lt; segment.start + i;\n\t\t\t}\n\t\t}\n\t\treturn s.str();\n\t}\n}</head-code></configuration><net id=\"101\" name=\"Main\"><area id=\"118\" sx=\"120\" sy=\"90\" x=\"-102\" y=\"-66\"><init x=\"-90\" y=\"-85\">all_processes(ctx)</init></area><place id=\"102\" label-x=\"-66\" label-y=\"-30\" name=\"segment\" radius=\"20\" sx=\"22\" sy=\"4\" x=\"-66\" y=\"-30\"><place-type x=\"-35\" y=\"-2\">Segment</place-type><init x=\"-49\" y=\"-60\" /><code>\tint s = (param::N() - 2) / ctx.process_count() + 1;\n\tSegment segment;\t\n\tsegment.start = ctx.process_id() * s + 2;\n\tif (segment.start + s &gt; param::N()) {\n\t\ts = param::N() - segment.start;\n\t}\n\tsegment.marks.resize(s, true);\n\tplace.add(segment);\n</code><trace trace-tokens=\"False\" /></place><place id=\"104\" label-x=\"66\" label-y=\"60\" name=\"number\" radius=\"20\" sx=\"12\" sy=\"6\" x=\"66\" y=\"60\"><place-type x=\"90\" y=\"84\">int</place-type><init x=\"90\" y=\"30\">[2]</init><trace trace-tokens=\"False\" /></place><place id=\"107\" label-x=\"240\" label-y=\"60\" name=\"next&#10;number\" radius=\"20\" sx=\"12\" sy=\"6\" x=\"240\" y=\"60\"><place-type x=\"270\" y=\"84\">int</place-type><init x=\"257\" y=\"30\" /><trace trace-tokens=\"False\" /></place><place id=\"109\" label-x=\"402\" label-y=\"-30\" name=\"prime\" radius=\"20\" sx=\"12\" sy=\"0\" x=\"402\" y=\"-30\"><place-type x=\"432\" y=\"-6\">int</place-type><init x=\"419\" y=\"-60\" /><trace trace-tokens=\"False\" /></place><transition clock=\"False\" collective=\"False\" id=\"103\" label-x=\"161\" label-y=\"-30\" name=\"Find&#10;prime\" priority=\"\" sx=\"70\" sy=\"36\" x=\"126\" y=\"-48\"><guard x=\"126\" y=\"-68\" /><code>\n\tint end = var.segment.start + var.segment.marks.size();\n\n\tif (var.num * var.num &gt; param::N()) {\t\t\n\t\tfor (int i = var.num; i &lt; end; i++) {\n\t\t\tif (var.segment.marks[i - var.segment.start]) {\t\t\n\t\t\t\tprintf(\"%i\\n\", i);\n\t\t\t}\n\t\t}\n\t} else {\n\t\tfor (int i = var.num; i &lt; end; i++) {\n\t\t\tif (var.segment.marks[i - var.segment.start]) {\t\t\n\t\t\t\tprintf(\"%i\\n\", i);\n\t\t\t\tvar.prime = i;\n\t\t\t\tvar.next_num = i+1;\n\t\t\t\tvar.targets = ca::range(ctx.process_id(), ctx.process_count());\n\t\t\t\treturn;\n\t\t\t}\n\t\t}\n\t}\n\tvar.prime = -1;\n\tvar.next_num = -1;\n\tint next = ctx.process_id() + 1;\n\tif (next == ctx.process_count()) {\n\t\tctx.quit();\n\t} else {\n\t\tvar.targets.push_back(next);\n\t}\n</code></transition><transition clock=\"False\" collective=\"False\" id=\"111\" label-x=\"161\" label-y=\"156\" name=\"Mark&#10;composites\" priority=\"\" sx=\"70\" sy=\"36\" x=\"126\" y=\"138\"><guard x=\"126\" y=\"118\" /><code>\tif (var.prime == -1) {\n\t\tvar.start.add(var.segment.start);\t\n\t} else {\n\t\tfor (int i = (var.prime - (var.segment.start % var.prime)) % var.prime; i &lt; var.segment.marks.size(); i += var.prime) {\n\t\t\tvar.segment.marks[i] = false;\n\t\t}\n\t}\n\t\n</code></transition><edge bidirectional=\"true\" from_item=\"102\" id=\"105\" to_item=\"103\"><inscription x=\"31.0\" y=\"-47.0\">segment</inscription></edge><edge from_item=\"104\" id=\"106\" to_item=\"103\"><inscription x=\"82.0\" y=\"2.0\">num</inscription><point x=\"72\" y=\"0\" /></edge><edge from_item=\"103\" id=\"108\" to_item=\"107\"><inscription x=\"252.0\" y=\"6.0\">[if(next_num &gt; 0)] next_num</inscription><point x=\"246\" y=\"0\" /></edge><edge from_item=\"103\" id=\"110\" to_item=\"109\"><inscription x=\"225.0\" y=\"-48.0\">[multicast] prime@targets</inscription></edge><edge from_item=\"109\" id=\"113\" to_item=\"111\"><inscription x=\"420.0\" y=\"68.0\">prime</inscription><point x=\"408\" y=\"156\" /></edge><edge from_item=\"107\" id=\"114\" to_item=\"111\"><inscription x=\"252.0\" y=\"108.0\">[bulk] start</inscription><point x=\"246\" y=\"126\" /></edge><edge from_item=\"111\" id=\"115\" to_item=\"104\"><inscription x=\"84.0\" y=\"108.0\">[bulk] start</inscription><point x=\"72\" y=\"126\" /></edge><edge bidirectional=\"true\" from_item=\"111\" id=\"116\" to_item=\"102\"><inscription x=\"-42.0\" y=\"66.0\">segment</inscription><point x=\"-54\" y=\"156\" /></edge></net><sequence name=\"Sequence23\">0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n3 0 S #111\n3 0 F\n1 0 S #111\n1 0 F\n0 0 S #111\n0 0 F\n2 0 S #111\n2 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n2 0 S #111\n2 0 F\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n0 0 S #111\n0 0 F\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n1 0 S #111\n1 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0</sequence><sequence name=\"XSequence\">0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n3 0 S #111\n3 0 F\n1 0 S #111\n1 0 F\n0 0 S #111\n0 0 F\n2 0 S #111\n2 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n2 0 S #111\n2 0 F\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n0 0 S #111\n0 0 F\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n0 0 S #111\n0 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n1 0 S #111\n1 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n3 0 S #111\n3 0 F\n0 0 S #111\n0 0 F\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n0 0 S #103\n0 0 F\n0 0 R 0\n1 0 R 0\n2 0 R 0\n3 0 R 0\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n0 0 S #111\n0 0 F\n3 0 S #111\n3 0 F\n0 0 S #103\n0 0 F\n1 0 R 0\n1 0 S #111\n1 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F\n1 0 S #111\n1 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n3 0 S #111\n3 0 F\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n2 0 S #111\n2 0 F\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n2 0 S #111\n2 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n2 0 S #111\n2 0 F\n1 0 S #111\n1 0 F\n3 0 S #111\n3 0 F\n1 0 S #103\n1 0 F\n1 0 R 1\n2 0 R 1\n3 0 R 1\n3 0 S #111\n3 0 F\n1 0 S #111\n1 0 F\n2 0 S #111\n2 0 F\n1 0 S #103\n1 0 F\n2 0 R 1\n2 0 S #111\n2 0 F\n2 0 S #103\n2 0 F\n2 0 R 2\n3 0 R 2\n2 0 S #111\n2 0 F\n3 0 S #111\n3 0 F</sequence></project>");
	std::vector<ca::Parameter*> parameters;
	parameters.push_back(&param::N);

	ca::init(argc, argv, parameters, false);

	ca::NetDef *def_101 = new ca::NetDef(0, 101, spawn_101);
	def_101->register_transition(&transition_103);
	def_101->register_transition(&transition_111);
	ca::NetDef *defs[] = {def_101};
	ca::setup(1, defs, true);
	ca::spawn_net(0);
	ca::main();
	return 0;
}
#line 1 "*103/function"
void transition_user_fn_103(ca::Context &ctx, Vars_103 &var)
{

	int end = var.segment.start + var.segment.marks.size();

	if (var.num * var.num > param::N()) {		
		for (int i = var.num; i < end; i++) {
			if (var.segment.marks[i - var.segment.start]) {		
				printf("%i\n", i);
			}
		}
	} else {
		for (int i = var.num; i < end; i++) {
			if (var.segment.marks[i - var.segment.start]) {		
				printf("%i\n", i);
				var.prime = i;
				var.next_num = i+1;
				var.targets = ca::range(ctx.process_id(), ctx.process_count());
				return;
			}
		}
	}
	var.prime = -1;
	var.next_num = -1;
	int next = ctx.process_id() + 1;
	if (next == ctx.process_count()) {
		ctx.quit();
	} else {
		var.targets.push_back(next);
	}
}
#line 1 "*111/function"
void transition_user_fn_111(ca::Context &ctx, Vars_111 &var)
{
	if (var.prime == -1) {
		var.start.add(var.segment.start);	
	} else {
		for (int i = (var.prime - (var.segment.start % var.prime)) % var.prime; i < var.segment.marks.size(); i += var.prime) {
			var.segment.marks[i] = false;
		}
	}
	
}
#line 1 "*102/init_function"
void place_user_fn_102(ca::Context &ctx, ca::TokenList<Segment > &place)
{
	int s = (param::N() - 2) / ctx.process_count() + 1;
	Segment segment;	
	segment.start = ctx.process_id() * s + 2;
	if (segment.start + s > param::N()) {
		s = param::N() - segment.start;
	}
	segment.marks.resize(s, true);
	place.add(segment);
}
