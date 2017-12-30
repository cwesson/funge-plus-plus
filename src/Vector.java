/**
 * @file Vector.java
 * Represents an N-dimensional vector.
 * @author Conlan Wesson
 */

import java.util.ArrayList;

class Vector{
	private ArrayList<Integer> values = new ArrayList<Integer>(3);

	public Vector(Vector orig){
		for(int i = 0; i < orig.values.size(); i++){
			setDimension(i, orig.getDimension(i));
		}
	}

	public Vector(){
		for(int i = 0; i < values.size(); i++){
			values.set(i, 0);
		}
	}
	
	public Vector(int x){
		this();
		this.setX(x);
	}
	
	public Vector(int x, int y){
		this(x);
		this.setY(y);
	}
	
	public Vector(int x, int y, int z){
		this(x, y);
		this.setZ(z);
	}

	public int getDimension(int dim){
		if(dim >= values.size()){
			return 0;
		}else{
			return values.get(dim);
		}
	}

	public void setDimension(int dim, int value){
		if(dim >= values.size()){
			for(int i = values.size(); i <= dim; i++){
				values.add(i, 0);
			}
		}
		values.set(dim, value);
	}
	
	public int size(){
		return values.size();
	}

	public int getX(){
		return getDimension(0);
	}

	public int getY(){
		return getDimension(1);
	}

	public int getZ(){
		return getDimension(2);
	}

	public void setX(int value){
		setDimension(0, value);
	}

	public void setY(int value){
		setDimension(1, value);
	}

	public void setZ(int value){
		setDimension(2, value);
	}
	
	public void set(int ... dim){
		for(int i = 0; i < values.size(); i++){
			setDimension(i, 0);
		}
		for(int i = 0; i < dim.length; i++){
			setDimension(i, dim[i]);
		}
	}
	
	public void reverse(){
		for(int i = 0; i < values.size(); i++){
			values.set(i, -values.get(i));
		}
	}
	
	public void left(){
		int tx = getX();
		int ty = getY();
		setX(ty);
		setY(-tx);
	}
	
	public void right(){
		int tx = getX();
		int ty = getY();
		setX(-ty);
		setY(tx);
	}
	
	public Vector add(Vector other){
		for(int i = 0; i < this.values.size() && i < other.values.size(); i++){
			this.setDimension(i, this.getDimension(i)+other.getDimension(i));
		}
		return this;
	}
}

