/**
 * @file Stack.java
 * Wrapper around Java Stack in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

@SuppressWarnings("serial")
public class Stack extends java.util.Stack<Integer>{
	public Integer pop(){
		int rtn = 0;
		try{
			rtn = super.pop();
		}catch(Exception e){
			rtn = 0;
		}
		return rtn;
	}
	
	public Integer peek(){
		int rtn = 0;
		try{
			rtn = super.peek();
		}catch(Exception e){
			rtn = 0;
		}
		return rtn;
	}
}

