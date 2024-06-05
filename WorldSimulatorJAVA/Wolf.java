package worldsimulator;

public class Wolf extends Animal {
	
    public Wolf(World w, Coordinate c) {
    	strength = Species.WOLF.getStrength();
        initiative = Species.WOLF.getInitiative();
        species = Species.WOLF.getName();
        sprite = Species.WOLF.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Wolf(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.WOLF.getInitiative();
        species = Species.WOLF.getName();
        sprite = Species.WOLF.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }
    
}
