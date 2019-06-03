/**
 * @file Field.java
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

import java.io.FileInputStream;
import java.io.File;
import java.io.IOException;
import java.io.PushbackInputStream;
import java.util.HashMap;

public class Field{
	private HashMap<Coordinate, Character> field = new HashMap<Coordinate, Character>();
	private int width = 0;
	private int height = 0;

	public Field(File file) throws IOException{
		PushbackInputStream fis = new PushbackInputStream(new FileInputStream(file));
		int x = 0;
		int y = 0;
		int z = 0;
		int i = 0;
		do{
			i = fis.read();
			if(i == '\n' || i == '\r' || i == -1){
				if(i == '\r'){
					int j = fis.read();
					if(j != '\n'){
						fis.unread(j);
					}
				}
				y++;
				x = 0;
				if(y > height && i != -1) {
					height = y;
				}
			}else if(i == '\f') {
				z++;
				x = 0;
				y = 0;
			}else{
				field.put(new Coordinate(x, y, z), (char)i);
				x++;
				if(x > width) {
					width = x;
				}
			}
		}while(i > -1);
		fis.close();
	}

	public int width(){
		return width;
	}

	public int height(){
		return height;
	}
	
	public void set(int x, int y, int v){
		field.put(new Coordinate(x, y), (char)v);
	}
	
	public int at(int x, int y){
		try {
			return field.get(new Coordinate(x, y));
		} catch(Exception e) {
			return ' ';
		}
	}
	
	public void set(int x, int y, int z, int v){
		field.put(new Coordinate(x, y, z), (char)v);
	}
	
	public int at(int x, int y, int z){
		try {
			return field.get(new Coordinate(x, y, z));
		} catch(Exception e) {
			return ' ';
		}
	}
}

