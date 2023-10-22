#include<stdio.h>
#include<stdlib.h>
#include "LEX.c"

void match();
void invalid(char*);
void valid();
void Program();
void declarations();
void data_type();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void expn();
void simple_expn();
void term();
void factor();
void tprime();
void mulop();
void seprime();
void addop();
void eprime();
void relop();
void looping_stat();
void decision_stat();
void dprime();
void switch_stat();
void case_stat();

struct token Token;
FILE* fp;
int DEFAULTCALL = 0;

void valid(){
	printf("---SUCCESS!---\n");
	exit(0);
}

void invalid(char* expected){
	printf("---ERROR!---\n");
	printf("Error at row %d and col %d\n",Token.row,Token.col);
	printf("Expected \"%s\"\n",expected);
	exit(0);
}

void match(){
	Token = getNextToken(fp);
}

void data_type(){
	if(strcmp(Token.lexeme,"int") == 0 || strcmp(Token.lexeme,"char") == 0){
		return;
	}
	else{
		invalid("int / char");
	}
}

void identifier_list(){
	if(strcmp(Token.type,"Identifier") == 0){
		match();
		if(strcmp(Token.lexeme,"[") == 0){
			match();
			if(strcmp(Token.type,"Number") == 0){
				match();
				if(strcmp(Token.lexeme,"]") == 0){
					match();
					if(strcmp(Token.lexeme,",") == 0){
						match();
						identifier_list();
					}
					if(strcmp(Token.type,"Identifier") == 0){
						invalid(",");
					}
					else{
						return;
					}
				}
				else{
					invalid("]");
				}
			}
			else{
				invalid("Number");
			}
		}
		if(strcmp(Token.lexeme,",") == 0){
			match();
			identifier_list();
		}

		if(strcmp(Token.type,"Identifier") == 0){
			invalid(",");
		}
		else{
			return;
		}
	}
	else{
		invalid("Identifier");
	}
}

void assign_stat(){
	if(strcmp(Token.type,"Identifier") == 0){
		match();
		if(strcmp(Token.lexeme,"=") == 0){
			match();
			expn();
		}
		else{
			invalid("=");
		}
	}
}

void expn(){
	simple_expn();
	eprime();
}

void simple_expn(){
	term();
	seprime();
}

void eprime(){
	if(strcmp(Token.lexeme,"==") == 0 || strcmp(Token.lexeme,"!=") == 0 || strcmp(Token.lexeme,"<") == 0 || strcmp(Token.lexeme,">") == 0  || strcmp(Token.lexeme,"<=") == 0 || strcmp(Token.lexeme,">=") == 0){
		relop();
		match();
		simple_expn();
	}
	else{
		return;
	}
}

void term(){
	factor();
	tprime();
}

void seprime(){
	if(strcmp(Token.lexeme,"+") == 0 || strcmp(Token.lexeme,"-") == 0){
		addop();
		match();
		term();
		seprime();				
	}
	else{
		return;
	}
}

void factor(){
	if(strcmp(Token.type,"Identifier") == 0 || strcmp(Token.type,"Number") == 0 || strcmp(Token.type,"CharacterLiteral") == 0){
		return;
	}
	else{
		invalid("Identifier/Number");
	}
}

void tprime(){
	match();
	if(strcmp(Token.lexeme,"*") == 0 || strcmp(Token.lexeme,"/") == 0 || strcmp(Token.lexeme,"%") == 0){
		mulop();
		match();
		factor();
		tprime();
	}
	else{
		return;
	}
}

void relop(){
	if(strcmp(Token.lexeme,"==") == 0){
		return;
	}
	else if(strcmp(Token.lexeme,"!=") == 0){
		return;
	}
	else if(strcmp(Token.lexeme,">=") == 0){
			return;
	}
	else if(strcmp(Token.lexeme,"<=") == 0){
				return;
	}
	else if(strcmp(Token.lexeme,"<") == 0){
			return;
	}
	else if(strcmp(Token.lexeme,">") == 0){
			return;
	}
	else{
		invalid("RELOP");
	}
}

void addop(){
	if(strcmp(Token.lexeme,"+") == 0 || strcmp(Token.lexeme,"-") == 0){
		return;
	}
	else{
		invalid("+/-");
	}
}

void mulop(){
	if(strcmp(Token.lexeme,"*") == 0 || strcmp(Token.lexeme,"/") == 0 || strcmp(Token.lexeme,"%") == 0){
		return;
	}
	else{
		invalid("* | / | %");
	}
}

void declarations(){
	data_type();
	match();
	identifier_list();
	if(strcmp(Token.lexeme,";") == 0){
		match();
		if(strcmp(Token.lexeme,"int") == 0 || strcmp(Token.lexeme,"char") == 0){
			declarations();
		}
		else{
			return;
		}
	}
	else{
		invalid(";");
	}
}

void statement_list(){
	if(strcmp(Token.type,"Identifier") == 0 || strcmp(Token.type,"Keyword") == 0){
		if(strcmp(Token.lexeme,"case") == 0 || strcmp(Token.lexeme,"default") == 0 || strcmp(Token.lexeme,"break") == 0)
			return;
		statement();
		statement_list();
	}
	else{
		if(strcmp(Token.lexeme,";") == 0){
			match();
		}
		return;
	}
}

void statement(){
	if(strcmp(Token.type,"Identifier")==0){
		assign_stat();

		if(strcmp(Token.lexeme,";") == 0){
			match();

			return;
		}
		else{
			invalid(";");
		}
	}
	decision_stat();
	looping_stat();
    switch_stat();
}

void decision_stat(){
	if(strcmp(Token.lexeme,"if") == 0){
		match();
		if(strcmp(Token.lexeme,"(") == 0){
			match();
			expn();
			if(strcmp(Token.lexeme,")") == 0){
				match();
				if(strcmp(Token.lexeme,"{") == 0){
					match();
					statement_list();
					if(strcmp(Token.lexeme,"}") == 0){
						match();
						dprime();
					}
					else{
						invalid("}");
					}
				}
				else{
					invalid("{");
				}	
			}
			else{
				invalid(")");
			}
		}
		else{
			invalid("(");
		}
	}
}

void looping_stat(){
	if(strcmp(Token.lexeme,"while") == 0){
		match();
		if(strcmp(Token.lexeme,"(") == 0){
			match();
			expn();
			if(strcmp(Token.lexeme,")") == 0){
				match();
				if(strcmp(Token.lexeme,"{") == 0){
					match();
					statement_list();
					if(strcmp(Token.lexeme,"}") == 0){
						match();
						return;
					}
					else{
						invalid("}");
					}
				}
				else{
					invalid("{");
				}	
			}
			else{
				invalid(")");
			}
		}
		else{
			invalid("(");
		}
	}
	else if(strcmp(Token.lexeme,"for") == 0){
		match();
		if(strcmp(Token.lexeme,"(") == 0){
			match();
			assign_stat();
			if(strcmp(Token.lexeme,";") == 0){
				match();
				expn();
				if(strcmp(Token.lexeme,";") == 0){
					match();
					assign_stat();
					if(strcmp(Token.lexeme,")") == 0){
						match();
						if(strcmp(Token.lexeme,"{") == 0){
							match();
							statement_list();
							if(strcmp(Token.lexeme,"}") == 0){
								match();
								return;
							}
							else{
								invalid("}");
							}	
						}
						else{
							invalid("{");
						}	
					}
					else{
						invalid(")");
					}
				}
				else{
					invalid(";");
				}
			}
			else{
				invalid(";");
			}
		}
		else{
			invalid("(");
		}
	}
}


void dprime(){
	if(strcmp(Token.lexeme,"else") == 0){
		match();
		if(strcmp(Token.lexeme,"{") == 0){
			match();
			statement_list();
			if(strcmp(Token.lexeme,"}") == 0){
				match();
				return;
			}
			else{
				invalid("}");
			}
		}
		else{
			invalid("{");
		}
	}
}

void switch_stat(){
    if(strcmp(Token.lexeme,"switch") == 0){
        match();
        if(strcmp(Token.lexeme,"(") == 0){
            match();
            expn();

            if(strcmp(Token.lexeme,")") == 0){
                match();
                if(strcmp(Token.lexeme,"{") == 0){
                    match();

                    if(strcmp(Token.lexeme,"case") == 0){
                        match();
                        expn();
                        if(strcmp(Token.lexeme,":") == 0){
                            match();
                            statement_list();
							if(strcmp(Token.lexeme,"break") == 0){
								match();
								if(strcmp(Token.lexeme,";") == 0){
									match();
								}
								else{
									invalid(";");
								}
							}
                            case_stat();
							if(strcmp(Token.lexeme,"}") == 0){
								return;
							}
							else{
								invalid("}");
							}
                        }
                        else{
                            invalid(":");
                        }
                    }
					else if(strcmp(Token.lexeme,"default") == 0){
						DEFAULTCALL = 1;
						match();
						if(strcmp(Token.lexeme,":") == 0){
							match();
							statement_list();
							if(strcmp(Token.lexeme,"break") == 0){
								match();
								if(strcmp(Token.lexeme,";") == 0){
									match();
								}
								else{
									invalid(";");
								}
							}
							case_stat();
							if(strcmp(Token.lexeme,"}") == 0){
								return;
							}
							else{
								invalid("}");
							}	
						}
						else{
							invalid(":");
						}
					}
                    else{
                        invalid("case");
                    }
                }
                else{
                    invalid("{");
                }
            }
            else{
                invalid(")");
            }
        }
        else{
            invalid("(");
        }
    }
}

void case_stat(){
	if(strcmp(Token.lexeme,"case") == 0){
		match();
		expn();
		if(strcmp(Token.lexeme,":") == 0){
			match();
			statement_list();
			if(strcmp(Token.lexeme,"break") == 0){
				match();
				if(strcmp(Token.lexeme,";") == 0){
					match();
				}
				else{
					invalid(";");
				}
			}
			case_stat();
		}
	}
	else if(strcmp(Token.lexeme,"default") == 0){
		if(DEFAULTCALL){
			invalid("case |||  Multiple defaults encountered ");
		}
		else{
			DEFAULTCALL = 1;
		}
		match();
		if(strcmp(Token.lexeme,":") == 0){
			match();
			statement_list();
			if(strcmp(Token.lexeme,"break") == 0){
				match();
				if(strcmp(Token.lexeme,";") == 0){
					match();
				}
				else{
					invalid(";");
				}
			}
			case_stat();
		}
	}
	else if(strcmp(Token.lexeme,"}") == 0){
		return;
	}
	else{
		invalid("case | default");
	}
}

void Program(){
	match();
	if(strcmp(Token.lexeme,"main") == 0){
		match();
		if(strcmp(Token.lexeme,"(") == 0){
			match();
			if(strcmp(Token.lexeme,")") == 0){
				match();
				if(strcmp(Token.lexeme,"{") == 0){
					match();
					declarations();
					statement_list();
					if(strcmp(Token.lexeme,"}") == 0){
						return;
					}
					else{
						invalid("}");
					}
				}
				else{
					invalid("{");
				}
			}
			else{
				invalid(")");
			}
		}
		else{
			invalid("(");
		}
	}
	else{
		invalid("main");
	}
}

int main(){
	fp = fopen("input.c","r");
	Program();
	valid();
}

/*
statement -> assign_stat; | decision_stat | looping_stat | switch_stat
switch_stat -> switch(expn){case expn: statement_list (break;)? case_stat | default: statement_list (break;)? case_stat}
case_stat-> case expn: statement_list case_stat | default: statement_list case_stat | epsilon
Make sure that default is used only once
*/