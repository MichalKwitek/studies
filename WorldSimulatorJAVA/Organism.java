package worldsimulator;

import java.util.List;
import java.util.Random;

public class Organism {
    protected char sprite;
    protected int initiative;
    protected int strength;
    protected int age;
    protected int id;
    protected boolean dead;
    protected String species;
    protected Coordinate coord;
    protected World world;

    public Organism() {
		// TODO Auto-generated constructor stub
	}
    
    public Organism(char sprite, int initiative, int strength, String species, Coordinate coord, World world) {
        this.sprite = sprite;
        this.initiative = initiative;
        this.strength = strength;
        this.species = species;
        this.coord = coord;
        this.world = world;
        this.age = 0;
        this.dead = false;
        this.id = -1; // ID will be set later
    }
    
    public void action() {
		// TODO Auto-generated method stub	
	}

    public Coordinate findSpace() {
        Coordinate newCoord = new Coordinate(coord);
        List<Coordinate> coordinates = world.getAdjacentTiles(newCoord);
        Random rand = new Random();
        while (newCoord.equals(coord)) {
            // Roll direction
            if (coordinates.size() > 0) {
            	int rolledValue = rand.nextInt(coordinates.size());
            	newCoord = coordinates.get(rolledValue);
            }
        }
        return newCoord;
    }
    
    public boolean spaceIsViable(Coordinate coord) {
    	// Check if the coordinate is within the bounds of the world
        if (!world.checkBoundaries(coord)) {
            return false;
        }
        // Check if there is an organism at the specified coordinate
        Organism org = world.findOrganismByCoordinate(coord);
        if (org != null) {
            return false;
        }
        // No organism with the specified coordinates found
        return true;
    }

    public Coordinate findVoidSpace(Coordinate coord) {
        Coordinate newCoord = new Coordinate(coord);
        List<Coordinate> coordinates = world.getAdjacentTiles(newCoord);
        // exclude all occupied tiles
        for (int i = coordinates.size() - 1; i >= 0; i--) {
        	if (world.findOrganismByCoordinate(coordinates.get(i)) != null) {
        		coordinates.remove(i);
        	}
        }
        if (coordinates.size() > 0) {
        	Random rand = new Random();
            int rolledValue = rand.nextInt(coordinates.size());
            newCoord = coordinates.get(rolledValue);
            return newCoord;
        }         
        return coord;
    }

    public void endTurn() {
        age += 1;
    }

    public int getIndex() {
        return Species.getSpeciesOrder(getSprite());
    }

    public Organism multiply(Organism org, Coordinate coord) {
        Organism newborn = null;
        Species species = Species.fromSprite(org.getSprite());
        switch (species) {
            case WOLF:
                newborn = new Wolf(world, coord);
                break;
            case SHEEP:
                newborn = new Sheep(world, coord);
                break;
            case ANTILOPE:
                newborn = new Antilope(world, coord);
                break;
            case TURTLE:
                newborn = new Turtle(world, coord);
                break;
            case FOX:
                newborn = new Fox(world, coord);
                break;
            case GRASS:
                newborn = new Grass(world, coord);
                break;
            case DANDELION:
                newborn = new Dandelion(world, coord);
                break;
            case GUARANA:
                newborn = new Guarana(world, coord);
                break;
            case NIGHTSHADE:
                newborn = new Nightshade(world, coord);
                break;
            case SOSNOWSKY:
                newborn = new Sosnowsky(world, coord);
                break;
		default:
			break;
        }
        newborn.setAge(-1);
        return newborn;
    }

    public void kill() {
        dead = true;
        coord = new Coordinate(-1, -1); // Setting the coordinate to (-1, -1) to signify death
    }

    public int getInitiative() {
        return initiative;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrength(int s) {
        strength = s;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int a) {
        age = a;
    }

    public void setInitiative(int i) {
        initiative = i;
    }

    public int getID() {
        return id;
    }

    public void setID(int index) {
        id = index;
    }

    public String getSpecies() {
        return species;
    }

    public char getSprite() {
        return sprite;
    }

    public boolean isDead() {
        return dead;
    }

    public Coordinate getCoord() {
        return coord;
    }

    public void setCoord(Coordinate c) {
        coord = c;
    }

    public int getXCoord() {
        return coord.x;
    }

    public int getYCoord() {
        return coord.y;
    }

    public boolean ranAway(Organism attacker) {
        return false;
    }

    public boolean hasDeflectedAttack(Organism attacker) {
        return false;
    }

    public boolean hasIncreasedStrength(Organism attacker) {
        System.out.println();
        return false;
    }

    public boolean isPoisonous(Organism attacker) {
        return false;
    }
}
