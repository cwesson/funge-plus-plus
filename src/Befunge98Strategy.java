/**
 * @file Befunge98Strategy.java
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

import java.time.LocalDateTime;

class Befunge98Strategy extends Unefunge98Strategy{
	public Befunge98Strategy(Field f, InstructionPointer i, StackStack s){
		super(f, i, s);
	}
	
	public boolean execute(char cmd){
		switch(cmd){
			// Befunge-93
			case '^':
				ip.setDir(0, -1); break;
			case 'v':
				ip.setDir(0, 1); break;
			case '|':
				if(stack.top().pop() == 0){
					ip.setDir(0, 1);
				}else{
					ip.setDir(0, -1);
				}
				break;
			case '?':{
				int r = rnd.nextInt(4);
				switch(r){
					case 0:
						ip.setDir(0, 1); break;
					case 1:
						ip.setDir(-1, 0); break;
					case 2:
						ip.setDir(1, 0); break;
					case 3:
						ip.setDir(0, -1); break;
				}
				break;
			}
			
			case '[':
				ip.left(); break;
			case ']':
				ip.right(); break;
			case 'w':{
				int b = stack.top().pop();
				int a = stack.top().pop();
				if(a < b){
					ip.left();
				}else if(a > b){
					ip.right();
				}
				break;
			}
			
			default:
				return super.execute(cmd);
		}
		return true;
	}
}

