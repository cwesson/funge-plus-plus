/**
 * @file Unefunge98Strategy.java
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

import java.time.LocalDateTime;

class Unefunge98Strategy extends Unefunge93Strategy{
	public Unefunge98Strategy(Field f, InstructionPointer i, StackStack s){
		super(f, i, s);
	}
	
	public boolean execute(char cmd){
		if(cmd >= 'a' && cmd <= 'f'){
			stack.top().push(cmd-'a'+10);
		}else if(cmd >= 'A' && cmd <= 'Z'){
			execute('r');
		}else{
			switch(cmd){
				case 'z': break; //No-op
				case '\'':{
					ip.next();
					stack.top().push((int)ip.get());
					break;
				}
				case ';':{
					do{
						ip.next();
					}while(ip.get() != ';');
					break;
				}
				case 'j':{
					int j = stack.top().pop();
					for(int i = 0; i < j; i++){
						ip.next();
					}
					break;
				}
				case 'k':{
					ip.next();
					char c = ip.get();
					int k = stack.top().pop();
					for(int i = 0; i < k; i++){
						execute(c);
					}
					break;
				}
				case 'n':
					stack.top().clear(); break;
				case 'q':{
					int r = stack.top().pop();
					System.exit(r);
					break;
				}
				case 'r':
					ip.reverse(); break;
				case 's':{
					ip.next();
					ip.set((char)(int)stack.top().pop());
					break;
				}
				case 't':{
					FungeRunner runner = new FungeRunner(field, new StackStack((Stack)stack.top().clone()), new InstructionPointer(ip));
					new Thread(runner).start();
					break;
				}
				case 'x':{
					int s = ip.getDimensions();
					for(int i = s-1; i >= 0; i--){
						ip.setDimension(i, stack.top().pop());
					}
					break;
				}
				case 'y':{
					pushSysInfo(stack.top().pop());
					break;
				}
				default:
					return super.execute(cmd);
			}
		}
		return true;
	}
	
	private void pushSysInfo(int num){
		int pushes = 26;
		// ENV variables
		stack.top().push(0);
		stack.top().push(0);
		// ARGV
		stack.top().push(0);
		stack.top().push(0);
		// Size of stacks
		for(int i = 0; i < stack.size(); i++){
			stack.top().push(stack.elementAt(i).size());
			pushes++;
		}
		// Number of stacks
		stack.top().push(stack.size());
		// Time
		LocalDateTime dt = LocalDateTime.now();
		stack.top().push(dt.getHour()*256*256 + dt.getMinute()*256 + dt.getSecond());
		// Date
		stack.top().push((dt.getYear()-1900)*256*256 + dt.getMonthValue()*256 + dt.getDayOfMonth());
		// Greatest non-space
		stack.top().push(0);
		stack.top().push(0);
		// Least non-space
		stack.top().push(0);
		stack.top().push(0);
		// Storage Offset
		stack.top().push(0);
		stack.top().push(0);
		// Delta vector
		stack.top().push(ip.getDX());
		stack.top().push(ip.getDY());
		// Current position
		stack.top().push(ip.getX());
		stack.top().push(ip.getY());
		// Team number
		stack.top().push(0);
		// Thread ID
		stack.top().push((int)(Thread.currentThread().getId()%Integer.MAX_VALUE));
		// Scalars per vector
		stack.top().push(2);
		// Path separator
		stack.top().push(47);
		// Operating Paradigm
		stack.top().push(0);
		// Version Number
		stack.top().push(1);
		// Handprint
		stack.top().push(0xC01AE550);
		// Bytes per cell
		stack.top().push(4);
		// Flags
		stack.top().push(0x11);
		if(num > 0){
			int val = 0;
			for(int i = 1; i <= num; i++){
				val = stack.top().pop();
			}
			for(int i = num; i < pushes; i++){
				int dis = stack.top().pop();
			}
			stack.top().push(val);
		}
	}
}

