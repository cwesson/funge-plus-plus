/**
 * @file InstructionPointer.java
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

class InstructionPointer{
	private Vector pos = new Vector(0, 0);
	private Vector delta = new Vector(1, 0);
	private Field field;

	public InstructionPointer(Field f){
		field = f;
	}

	public InstructionPointer(InstructionPointer ip){
		pos = new Vector(ip.pos);
		delta = new Vector(ip.delta);
		field = ip.field;
		this.reverse();
		this.next();
	}

	public char get(){
		return (char)field.at(pos.getX(), pos.getY());
	}

	public void set(char val){
		field.set(pos.getX(), pos.getY(), val);
	}
	
	public void next(){
		pos.add(delta);
		// Lahey space wrapping
		if(pos.getX() < 0 || pos.getX() >= field.width() || pos.getY() < 0 || pos.getY() >= field.height()){
			delta.reverse();
			next();
			while(pos.getX() >= 0 && pos.getX() < field.width() && pos.getY() >= 0 && pos.getY() < field.height()){
				pos.add(delta);
			}
			delta.reverse();
			pos.add(delta);
		}
	}
	
	public void reverse(){
		delta.reverse();
	}
	
	public void left(){
		delta.left();
	}
	
	public void right(){
		delta.right();
	}
	
	public void setDir(int ... d){
		delta.set(d);
	}
	
	public void setDimension(int dim, int value){
		delta.setDimension(dim, value);
	}
	
	public int getDimensions(){
		return delta.size();
	}
	
	public int getX(){
		return pos.getX();
	}
	
	public int getY(){
		return pos.getY();
	}
	
	public int getZ(){
		return pos.getZ();
	}
	
	public int getDX(){
		return delta.getX();
	}
	
	public int getDY(){
		return delta.getY();
	}
	
	public int getDZ(){
		return delta.getZ();
	}
	
	public void stop(){
		setDir(0, 0);
	}
	
	public boolean isStopped(){
		boolean ret = true;
		for(int i = 0; i < delta.size(); i++){
			ret = ret && (delta.getDimension(i) == 0);
		}
		return ret;
	}
}

