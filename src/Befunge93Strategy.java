/**
 * @file Befunge93Strategy.java
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

class Befunge93Strategy extends Unefunge93Strategy{
	public Befunge93Strategy(Field f, InstructionPointer i, StackStack s){
		super(f, i, s);
	}
	
	public boolean execute(char cmd){
		switch(cmd){
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
			default:
				return super.execute(cmd);
		}
		return true;
	}
}

