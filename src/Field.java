/**
 * @file Field.java
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

import java.io.FileInputStream;
import java.io.File;
import java.io.IOException;
import java.io.PushbackInputStream;

public class Field{
	private int[][] code;
	
	public Field(File file, int width, int height) throws IOException{
		PushbackInputStream fis = new PushbackInputStream(new FileInputStream(file));
		code = new int[width][height];
		int x = 0;
		int y = 0;
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
				for(; x < width; x++){
					code[x][y] = ' ';
				}
				y++;
				x = 0;
			}else{
				code[x][y] = (char)i;
				x++;
			}
		}while(i > -1);
	}

	public int width(){
		return code.length;
	}

	public int height(){
		return code[0].length;
	}
	
	public void set(int x, int y, int v){
		code[x][y] = v;
	}
	
	public int at(int x, int y){
		return code[x][y];
	}
}

