/**
 * @file Unefunge93Strategy.java
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

class Unefunge93Strategy extends FungeStrategy{
	protected Random rnd = new Random();
	protected Scanner scan = new Scanner(System.in);
	
	public Unefunge93Strategy(Field f, InstructionPointer i, StackStack s){
		super(f, i, s);
	}
	
	public boolean execute(char cmd){
		if(cmd >= '0' && cmd <= '9'){
			stack.top().push(cmd-'0');
		}else{
			switch(cmd){
				case '!':
					if(stack.top().pop() == 0){
						stack.top().push(1);
					}else{
						stack.top().push(0);
					}
					break;
				case '#':
					ip.next(); break;
				case '$':
					stack.top().pop(); break;
				
				// Operators
				case '%':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(b%a);
					break;
				}
				case '*':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(a*b);
					break;
				}
				case '+':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(a+b);
					break;
				}
				case '-':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(b-a);
					break;
				}
				
				//Output
				case ',':{
					int x = stack.top().pop().intValue();
					System.out.print((char)x);
					if(x == 10){ System.out.flush(); }
					break;
				}
				case '.':
					System.out.print(stack.top().pop()+" "); break;
				
				case '/':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(b/a);
					break;
				}
				case ':':{
					int x = stack.top().pop();
					stack.top().push(x);
					stack.top().push(x);
					break;
				}
				case '<':
					ip.setDir(-1, 0); break;
				case '>':
					ip.setDir(1, 0); break;
				case '?':{
					int r = rnd.nextInt(2);
					switch(r){
						case 0:
							ip.setDir(-1, 0); break;
						case 1:
							ip.setDir(1, 0); break;
					}
					break;
				}
				case '@':
					ip.stop(); break;
				case '\\':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					stack.top().push(a);
					stack.top().push(b);
					break;
				}
				case '_':
					if(stack.top().pop() == 0){
						ip.setDir(1, 0);
					}else{
						ip.setDir(-1, 0);
					}
					break;
				case '`':{
					int a = stack.top().pop();
					int b = stack.top().pop();
					if(b > a){
						stack.top().push(1);
					}else{
						stack.top().push(0);
					}
					break;
				}
				//Self-Modifying
				case 'g':{
					int gy = stack.top().pop();
					int gx = stack.top().pop();
					stack.top().push((int)field.at(new Vector(gx,gy)));
					break;
				}
				case 'p':{
					int y = stack.top().pop();
					int x = stack.top().pop();
					int v = stack.top().pop();
					field.set(new Vector(x,y),v);
					break;
				}
				//Input
				case '&':
					stack.top().push(scan.nextInt()); break;
				case '~':{
					try{
						int q = System.in.read();
						if(q == 13){
							q = System.in.read();
						}
						stack.top().push(q);
					}catch(IOException e){}
					break;
				}
				
				default:
					return false;
			}
		}
		return true;
	}
}
