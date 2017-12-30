/**
 * @file Trefunge98Strategy.java
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */


class Trefunge98Strategy extends Befunge98Strategy{
	public Trefunge98Strategy(Field f, InstructionPointer i, StackStack s){
		super(f, i, s);
	}
	
	public boolean execute(char cmd){
		switch(cmd){
			case 'h':
				ip.setDir(0, 0, -1);
				break;
			case 'l':
				ip.setDir(0, 0, 1);
				break;
			case 'm':
				if(stack.top().pop() != 0){
					ip.setDir(0, 0, -1);
				}else{
					ip.setDir(0, 0, 1);
				}
				break;
			
			default:
				return super.execute(cmd);
		}
		return true;
	}
}

