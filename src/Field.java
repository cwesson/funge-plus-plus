/**
 * @file Field.java
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

import java.io.FileInputStream;
import java.io.File;
import java.io.IOException;
import java.io.PushbackInputStream;
import java.util.ArrayList;
import java.util.HashMap;

public class Field{
	private HashMap<Vector, Character> field = new HashMap<Vector, Character>();
	private ArrayList<Integer> max = new ArrayList<Integer>();

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
			}else if(i == '\f') {
				z++;
				x = 0;
				y = 0;
			}else{
				this.set(new Vector(x, y, z), (char)i);
				x++;
			}
		}while(i > -1);
		fis.close();
	}

	public int width(){
		return max.get(0);
	}

	public int height(){
		return max.get(1);
	}
	
	public void set(Vector p, int v){
		for(int i = 0; i < p.size(); i++) {
			if(i >= max.size()){
				for(int j = max.size(); j <= i; j++){
					max.add(j, 0);
				}
			}
			if(max.get(i) < p.getDimension(i)+1) {
				max.set(i, p.getDimension(i)+1);
			}
		}
		field.put(p, (char)v);
	}
	
	public int at(Vector p){
		try {
			return field.get(p);
		} catch(Exception e) {
			return ' ';
		}
	}
}

