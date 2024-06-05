package worldsimulator;

public class Human extends Animal {
    private static final int SUPER_STRENGTH_INCREASE = 5;
	private int superStrengthTimer;
	private Directions moveDirection;
    
    public Human(World w, Coordinate c) {
    	superStrengthTimer = 0;
    	strength = Species.HUMAN.getStrength();
        initiative = Species.HUMAN.getInitiative();
        species = Species.HUMAN.getName();
        sprite = Species.HUMAN.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Human(World w, Coordinate c, int s, int a, int ss) {
    	superStrengthTimer = ss;
    	strength = s;
    	initiative = Species.HUMAN.getInitiative();
        species = Species.HUMAN.getName();
        sprite = Species.HUMAN.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }
    
    @Override
    public void kill() {
        dead = true;
        coord = new Coordinate(-1, -1); // Setting the coordinate to (-1, -1) to signify death
        world.killHuman();
    }
    
    public boolean canHumanMove() {
    	if (moveDirection == null) {
    		return false;
    	}
    	Coordinate newCoord = new Coordinate (getCoord());
    	if (world instanceof GridWorld) {
        	switch (moveDirection) {
            case NORTH:
                newCoord.y -= 1;
                break;
            case EAST:
                newCoord.x += 1;
                break;
            case SOUTH:
                newCoord.y += 1;
                break;
            case WEST:
                newCoord.x -= 1;
                break;
			default:
				break;
            }
        } else if (world instanceof HexWorld) {
        	switch (moveDirection) {
        	case NORTH:
                newCoord.x -= 1;
                newCoord.y += 1;
                break;
            case NORTH_EAST:
            	newCoord.x -= 1;
                break;
            case NORTH_WEST:
            	newCoord.y += 1;
                break;
            case SOUTH_EAST:
            	newCoord.y -= 1;
                break;
            case SOUTH_WEST:
            	newCoord.x += 1;
                break;
            case SOUTH:
            	newCoord.x += 1;
                newCoord.y -= 1;
                break;
			default:
				break;
            }
        }
    	if (!world.checkBoundaries(newCoord) || newCoord.equals(coord)) {
            return false;
        } else {
            return true;
        }
    }
    
    @Override
    public void action() {
    	String message;
        Coordinate newCoord = new Coordinate (getCoord());
        if (world instanceof GridWorld) {
        	switch (moveDirection) {
            case NORTH:
                newCoord.y -= 1;
                break;
            case EAST:
                newCoord.x += 1;
                break;
            case SOUTH:
                newCoord.y += 1;
                break;
            case WEST:
                newCoord.x -= 1;
                break;
			default:
				break;
            }
        } else if (world instanceof HexWorld) {
        	switch (moveDirection) {
        	case NORTH:
                newCoord.x -= 1;
                newCoord.y += 1;
                break;
            case NORTH_EAST:
            	newCoord.x -= 1;
                break;
            case NORTH_WEST:
            	newCoord.y += 1;
                break;
            case SOUTH_EAST:
            	newCoord.y -= 1;
                break;
            case SOUTH_WEST:
            	newCoord.x += 1;
                break;
            case SOUTH:
            	newCoord.x += 1;
                newCoord.y -= 1;
                break;
			default:
				break;
            }
        }
        Organism opponent = world.findOrganismByCoordinate(newCoord);
        message = String.format(getSpecies() + " przechodzi z pola " + getCoord() + " na pole " + newCoord);
        world.prompt(message);
        if (opponent == null) {
            setCoord(newCoord);
            message = String.format("\n");
            world.prompt(message);
        } else {
            collision(this, opponent);
        }
    }

    public void activateSuperStrength() {
    	String message;
        if (superStrengthTimer == 0) {
            superStrengthTimer = 10;
            message = String.format("Aktywowano zdolnosc specjalna");
            world.prompt(message);
            message = String.format(getSpecies() + " zwieksza swoja sile z " + getStrength() + " do " + (getStrength() + SUPER_STRENGTH_INCREASE));
            world.prompt(message);
            setStrength(getStrength() + SUPER_STRENGTH_INCREASE);
        } else {
        	message = String.format("Jeszcze nie mozna aktywowac zdolnosci specjalnej");
        	world.prompt(message);
        }
    }

    @Override
    public void endTurn() {
        super.endTurn();
        if (superStrengthTimer > 5) {
        	String message = String.format("Sila " + getSpecies() + " spada o 1 z " + getStrength() + " do " + (getStrength() - 1));
            world.prompt(message);
            strength -= 1;
        }
        if (superStrengthTimer != 0) {
        	superStrengthTimer -= 1;
        }
        moveDirection = null;
    }

    public void setSuperStrengthTimer(int timer) {
        superStrengthTimer = timer;
    }
    
    public void setMoveDirection(Directions dir) {
        moveDirection = dir;
    }

    public int getSuperStrengthTimer() {
        return superStrengthTimer;
    }
    
    public Directions getMoveDirection() {
        return moveDirection;
    }

}
