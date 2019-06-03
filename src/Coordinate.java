import java.util.ArrayList;


public class Coordinate{
	private ArrayList<Integer> values = new ArrayList<Integer>(3);

	public Coordinate(Coordinate orig){
		for(int i = 0; i < orig.values.size(); i++){
			setDimension(i, orig.getDimension(i));
		}
	}

	public Coordinate(){
		for(int i = 0; i < values.size(); i++){
			values.set(i, 0);
		}
	}

	public Coordinate(int ... v) {
		for(int d = 0; d < v.length; d++){
			this.setDimension(d, v[d]);
		}
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
	
	@Override
	public int hashCode() {
		int hash = 1;
		for(int i : values) {
			hash *= i+1;
		}
		return hash;
	}
	
	@Override
	public boolean equals(Object obj) {
		try {
			Coordinate other = (Coordinate)obj;
			int max = Math.max(this.size(), other.size());
			for(int i = 0; i < max; i++) {
				if(this.getDimension(i) != other.getDimension(i)) {
					return false;
				}
			}
			return true;
		}catch(Exception e) {
			return false;
		}
	}
}
