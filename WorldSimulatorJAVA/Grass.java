package worldsimulator;

public class Grass extends Plant {
	
	public Grass(World w, Coordinate c) {
		strength = Species.GRASS.getStrength();
        initiative = Species.GRASS.getInitiative();
        species = Species.GRASS.getName();
        sprite = Species.GRASS.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Grass(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.GRASS.getInitiative();
        species = Species.GRASS.getName();
        sprite = Species.GRASS.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }
}
