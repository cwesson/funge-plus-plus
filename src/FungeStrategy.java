/**
 * @file FungeStrategy.java
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

abstract class FungeStrategy{
	protected Field field;
	protected InstructionPointer ip;
	protected StackStack stack;
	
	public FungeStrategy(Field f, InstructionPointer i, StackStack s){
		field = f;
		ip = i;
		stack = s;
	}
	
	abstract public boolean execute(char cmd);
}

