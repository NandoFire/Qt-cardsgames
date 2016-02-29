// VBParser.h

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {


////////////////////////////////////////////////////////////////////
//
// VBParser
//
/////////////////////////////////////////////////////////////////////

const int VB_NUMVARS = 26;
enum VB_typesT { UNDEFTOK, OPERATOR, NUMBER, VARIABLE };
enum VB_errorsT { SERROR, PARENS, NOEXP, DIVZERO };

template <class PType> 
class VBParser {
	const char *exp_ptr;  // points to the expression
	char token[80]; // holds current token
	VB_typesT tok_type;  // holds token's type
	PType vars[VB_NUMVARS]; // holds variable's values
	
	void eval_exp1(PType &result);
	void eval_exp2(PType &result);
	void eval_exp3(PType &result);
	void eval_exp4(PType &result);
	void eval_exp5(PType &result);
	void eval_exp6(PType &result);
	void atom(PType &result);
	void get_token();
	void putback();
	void serror(VB_errorsT error);
	PType find_var(char *s);
	bool isdelim(char c);
public:
	VBParser();
	PType eval_exp(const char *exp);
};

// Constructor
template <class PType> 
VBParser<PType>::VBParser()
{
	int i;
	exp_ptr = 0;
	for(i=0; i<VB_NUMVARS; i++) 
		vars[i] = (PType) 0;
}

// VBParser entry point.
template <class PType> 
PType VBParser<PType>::eval_exp(const char *exp)
{
	PType result;
	exp_ptr = exp;
	get_token();
	if(!*token) {
		serror(NOEXP); // no expression present
		return (PType) 0;
	}
	eval_exp1(result);
	if(*token) serror(SERROR); // last token must be null
	return result;
}

// Process an assignment.
template <class PType> 
void VBParser<PType>::eval_exp1(PType &result)
{
	int slot;
	VB_typesT ttok_type;
	char temp_token[80];
	
	if(tok_type==VARIABLE) {
		// save old token
		strcpy(temp_token, token);
		ttok_type = tok_type;
		
		// compute the index of the variable
		slot = toupper(*token) - 'A';
		
		get_token();
		if(*token != '=') {
			putback(); // return current token
			// restore old token - not assignment
			strcpy(token, temp_token);
			tok_type = ttok_type;
		}
		else {
			get_token(); // get next part of exp
			eval_exp2(result);
			vars[slot] = result;
			return;
		}
	}
	
	eval_exp2(result);
}

// Add or subtract two terms.
template <class PType> 
void VBParser<PType>::eval_exp2(PType &result)
{
	register char op;
	PType temp;
	
	eval_exp3(result);
	while((op = *token) == '+' || op == '-') {
		get_token();
		eval_exp3(temp);
		switch(op) {
		case '-':
			result = result - temp;
			break;
		case '+':
			result = result + temp;
			break;
		}
	}
}

// Multiply or divide two factors.
template <class PType> 
void VBParser<PType>::eval_exp3(PType &result)
{
	register char op;
	PType temp;
	
	eval_exp4(result);
	while((op = *token) == '*' || op == '/' || op == '%') {
		get_token();
		eval_exp4(temp);
		switch(op) {
		case '*':
			result = result * temp;
			break;
		case '/':
			if(!temp) serror(DIVZERO); // division by zero attempted
			else result = result / temp;
			break;
		case '%':
			result = (int) result % (int) temp;
			break;
		}
	}
}

// Process an exponent.
template <class PType> 
void VBParser<PType>::eval_exp4(PType &result)
{
	PType temp, ex;
	
	eval_exp5(result);
	if(*token== '^') {
		get_token();
		eval_exp4(temp);
		ex = result;
		if(temp== (PType) 0) {
			result = (PType) 1;
			return;
		}
		//  register int t;
		//    for(t=(int)temp-1; t>0; --t) result = result * ex;
		result = (PType) pow (ex,temp);
	}
}

// Evaluate a unary + or -.
template <class PType> 
void VBParser<PType>::eval_exp5(PType &result)
{
	register char  op;
	
	op = 0;
	if((tok_type == OPERATOR) && *token=='+' || *token == '-') {
		op = *token;
		get_token();
	}
	eval_exp6(result);
	if(op=='-') result = -result;
}

// Process a parenthesized expression.
template <class PType> 
void VBParser<PType>::eval_exp6(PType &result)
{
	if((*token == '(')) {
		get_token();
		eval_exp2(result);
		if(*token != ')')
			serror(PARENS);
		get_token();
	}
	else atom(result);
}

// Get the value of a number or a variable.
template <class PType> 
void VBParser<PType>::atom(PType &result)
{
	switch(tok_type) {
    case VARIABLE:
		result = find_var(token);
		get_token();
		return;
    case NUMBER:
		result = (PType) atof(token);
		get_token();
		return;
    default:
		serror(SERROR);
	}
}

// Return a token to the input stream.
template <class PType> 
void VBParser<PType>::putback()
{
	char *t;
	
	t = token;
	for(; *t; t++) exp_ptr--;
}

// Display a syntax error.
template <class PType> 
void VBParser<PType>::serror(VB_errorsT error)
{
	static const char *e[]= {
		"Syntax Error",
			"Unbalanced Parentheses",
			"No expression Present",
			"Division by zero"
	};
	std::cout << e[error] << std::endl;
}

// Obtain the next token.
template <class PType> 
void VBParser<PType>::get_token()
{
	register char *temp;
	
	tok_type = UNDEFTOK;
	temp = token;
	*temp = '\0';
	
	if(!*exp_ptr) return; // at end of expression
	
	while(isspace(*exp_ptr)) ++exp_ptr; // skip over white space
	
	if(strchr("+-*/%^=()", *exp_ptr)){
		tok_type = OPERATOR;
		// advance to next char
		*temp++ = *exp_ptr++;
	}
	else if(isalpha(*exp_ptr)) {
		while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		tok_type = VARIABLE;
	}
	else if(isdigit(*exp_ptr)) {
		while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		tok_type = NUMBER;
	}
	
	*temp = '\0';
}

// Return true if c is a delimiter.
template <class PType> 
bool VBParser<PType>::isdelim(char c)
{
	if(strchr(" +-/*%^=()", c) || c==9 || c=='\r' || c==0)
		return true;
	return false;
}

// Return the value of a variable.
template <class PType> 
PType VBParser<PType>::find_var(char *s)
{
	if(!isalpha(*s)){
		serror(SERROR);
		return (PType) 0;
	}
	return vars[toupper(*token)-'A'];
}


////////////////////////////////////////////////////////////////////
// Definition of types based on generic class VBParser
/////////////////////////////////////////////////////////////////////

typedef VBParser<float> VBParser_F;
typedef VBParser<double> VBParser_D;
typedef VBParser<long double> VBParser_LD;

}}}} // close namespace ::br::com::sbVB::VBMath
