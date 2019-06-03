/**
 * @file StackStack.java
 * Stack of Stacks
 * @author Conlan Wesson
 */

class StackStack extends java.util.Stack<Stack>{
	public StackStack(){
		super.push(new Stack());
	}

	public StackStack(Stack stack){
		super.push(stack);
	}

	public Stack top(){
		return super.elementAt(0);
	}

	public Stack second(){
		return super.elementAt(1);
	}

	public Stack pop(){
		Stack ret = super.pop();
		if(super.size() == 0){
			super.push(new Stack());
		}
		return ret;
	}
	
	public Stack push(Stack s) {
		super.push(s);
		return super.elementAt(0);
	}
}

