package worldsimulator;

public class Fox extends Animal {
	
    public Fox(World w, Coordinate c) {
    	strength = Species.FOX.getStrength();
        initiative = Species.FOX.getInitiative();
        species = Species.FOX.getName();
        sprite = Species.FOX.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Fox(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.FOX.getInitiative();
        species = Species.FOX.getName();
        sprite = Species.FOX.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }
    
    @Override
    public void action() {
    	String message;
        Coordinate newCoord;
        Organism opponent = null;
        boolean canMove = false;
        newCoord = findSpace(); // wybierz sąsiednie pole
        opponent = world.findOrganismByCoordinate(newCoord);
        if (opponent != null) {
            // jesli przeciwnik ma wyższą siłę i nie jest lisem (guarana zwiększa siłę) to trzeba wybrać inne miejsce
            if ((opponent.getStrength() > getStrength()) && (!opponent.getSpecies().equals(getSpecies()))) {
            	message = String.format("Dzieki dobremu wechowi " + getSpecies() + getID() + " z pola " + getCoord() + " unika niebezpieczenstwa ze strony " + opponent.getSpecies() + opponent.getID() + " na polu " + opponent.getCoord());
                world.prompt(message);
            	newCoord = findVoidSpace(getCoord());
                if (!newCoord.equals(getCoord())) {// check if there is any space left around - if not then fox cannot shun the opponent
                    canMove = true;
                    opponent = world.findOrganismByCoordinate(newCoord);
                } else { // if there is no space left stay in the same place
                	message = String.format(getSpecies() + getID() + " pozostaje na polu " + getCoord() + " - brak miejsca niezajetego przez silniejszego przeciwnika\n");
                    world.prompt(message);
                	return;
                }
            } else {
                canMove = true;
            }
        } else {
            canMove = true;
        }
        if (canMove) {
        	message = String.format(getSpecies() + getID() + " przechodzi z pola " + getCoord() + " na pole " + newCoord);
        	world.prompt(message);
        }
        if (opponent == null) {
        	message = String.format(" ");
        	world.prompt(message);
            setCoord(newCoord);
        } else {
            collision(this, opponent);
        }
    }

    @Override
    public boolean spaceIsViable(Coordinate coord) {
        if (!world.checkBoundaries(coord)) {
            return false;
        }
        Organism org = world.findOrganismByCoordinate(coord);
        // jesli przeciwnik ma wyższą siłę i nie jest lisem (guarana zwiększa siłę) to zwróć false
        if (org != null) {
        	if ((org.getStrength() > getStrength()) && !org.getSpecies().equals(getSpecies())) {
                return false;
            }
        }
        return true; // No Organism with the specified coordinates found
    }
}
