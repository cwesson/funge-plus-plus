/**
 * @file FungeRunner.java
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */


/**
 * Runs Befunge code.
 * Implemented instructions:
 * ! " # $ % & ' * + , - . / 0-9 : ; < > ? @ [ \ ]
 * ^ _ ` A-Z a-f g j k n p q r s t v w x y z | ~
 */
public class FungeRunner implements Runnable{
	private static Object mutex = new Object();
	private boolean str = false;
	private Field field;
	private StackStack stack;
	private InstructionPointer ip;
	private FungeStrategy strategy;

	public FungeRunner(Field field) {
		this(field, new StackStack(), new InstructionPointer(field));
	}

	public FungeRunner(Field field, StackStack stack, InstructionPointer ip){
		this.field = field;
		this.stack = stack;
		this.ip = ip;
		strategy = new Befunge98Strategy(field, ip, stack);
	}

	public void run(){
		try{
			while(!ip.isStopped()){
				synchronized(mutex){
					char i = ip.get();
					if(str){
						if(i != '\"'){
							stack.top().push((int)i);
						}else{
							str = false;
						}
					}else if(i == '\"'){
						str = true;
					}else if(i != ' '){
						execute(i);
					}
					ip.next();
				}
				Thread.yield();
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	private void execute(char cmd){
		boolean ret = strategy.execute(cmd);
		if(!ret){
			System.err.println("Unimplemented instruction "+(int)cmd+" \'"+cmd+"\' at "+ip+".");
		}
	}
}

