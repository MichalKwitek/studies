package worldsimulator;

public class Animal extends Organism {
	public Animal(char sprite, int initiative, int strength, String species, Coordinate coord, World world) {
		super(sprite, initiative, strength, species, coord, world);
		// TODO Auto-generated constructor stub
	}

	public Animal() {
		// TODO Auto-generated constructor stub
	}

	@Override
    public void action() {
		String message;
        Coordinate newCoord = findSpace();
        Organism opponent = world.findOrganismByCoordinate(newCoord);
        message = String.format(getSpecies() + getID() + " przechodzi z pola " + getCoord() + " na pole " + newCoord);
        world.prompt(message);
        if (opponent == null) {
            setCoord(newCoord);
            message = String.format(" ");
            world.prompt(message);
        } else {
            collision(this, opponent);
        }
    }

    protected void collision(Animal initiator, Organism opponent) {
    	String message = String.format(initiator.getSpecies() + initiator.getID() + " napotyka " + opponent.getSpecies() + opponent.getID() + " na polu " + opponent.getCoord());
        world.prompt(message);
    	if (initiator.getSpecies().equals(opponent.getSpecies())) {
            Coordinate newbornCoord = findVoidSpace(opponent.getCoord());
            if (!newbornCoord.equals(opponent.getCoord())) {
                Organism newborn = multiply(opponent, newbornCoord);
                message = String.format("Narodzilo sie nowe zwierze: " + newborn.getSpecies() + newborn.getID() + " na polu " + newbornCoord);
                world.prompt(message);
            } else {
            	message = String.format("Nowe zwierze: " + getSpecies() + " nie moze sie narodzic - brak pustego miejsca w poblizu");
            	world.prompt(message);
            }
            message = String.format(initiator.getSpecies() + initiator.getID() + " wraca na pole " + initiator.getCoord() + "\n");
            world.prompt(message);
    	} else {
            fight(initiator, opponent);
        }
    }

    protected void fight(Animal initiator, Organism opponent) {
        if (opponent instanceof Animal) {
            if (!opponent.ranAway(initiator) && !opponent.hasDeflectedAttack(initiator)) {
                if (initiator.getStrength() < opponent.getStrength()) {
                	String message = String.format("Walka: " + initiator.getSpecies() + initiator.getID() + " przegrywa z " + opponent.getSpecies() + opponent.getID() + "\n");
                    world.prompt(message);
                	initiator.kill();
                } else {
                	String message = String.format("Walka: " + initiator.getSpecies() + initiator.getID() + " pokonuje " + opponent.getSpecies() + opponent.getID() + "\n");
                    world.prompt(message);
                	initiator.setCoord(opponent.getCoord());
                    opponent.kill();
                }
            }
        } else {
            if (!opponent.isPoisonous(initiator)) {
            	String message = String.format(initiator.getSpecies() + initiator.getID() + " zjada " + opponent.getSpecies() + opponent.getID() + " na polu " + opponent.getCoord() + "\n");
                world.prompt(message);
            	opponent.hasIncreasedStrength(initiator);
                initiator.setCoord(opponent.getCoord());
                opponent.kill();
            }
        }
    }
}
