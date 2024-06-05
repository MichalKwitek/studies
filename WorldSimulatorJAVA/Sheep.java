package worldsimulator;

public class Sheep extends Animal {
	
	public Sheep(World w, Coordinate c) {
		strength = Species.SHEEP.getStrength();
        initiative = Species.SHEEP.getInitiative();
        species = Species.SHEEP.getName();
        sprite = Species.SHEEP.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Sheep(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.SHEEP.getInitiative();
        species = Species.SHEEP.getName();
        sprite = Species.SHEEP.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

}
