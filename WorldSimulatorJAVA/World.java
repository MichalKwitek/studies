package worldsimulator;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public abstract class World {
    protected List<Organism> organisms;
    protected int turn;
    protected int[] speciesCounter;
    protected GameMenu gameMenu;
    protected Human human;
    
    public void setGameMenu(GameMenu gameMenu) {
        this.gameMenu = gameMenu;
    }
    
    public World() {
        organisms = new ArrayList<>();
        turn = 0;
        speciesCounter = new int[Constants.SPECIES_NUMBER];
        for (int i = 0; i < Constants.SPECIES_NUMBER; ++i) {
            speciesCounter[i] = 0;
        }
    }

    public World(int height, int width) {
        organisms = new ArrayList<>();
        turn = 0;
        speciesCounter = new int[Constants.SPECIES_NUMBER];
        for (int i = 0; i < Constants.SPECIES_NUMBER; ++i) {
            speciesCounter[i] = 0;
        }
    }
    
    public abstract List<Coordinate> getAdjacentTiles (Coordinate coord);

    public Organism findOrganismByCoordinate(Coordinate coord) {
        for (Organism org : organisms) {
            if (org.getCoord().equals(coord) && !org.isDead()) {
                return org; // Return the pointer to the organism if found
            }
        }
        return null; // Return null if no organism with the specified coordinate is found
    }

    public boolean spaceIsOccupied(Coordinate coord) {
        for (Organism org : organisms) {
            if (org.getCoord().equals(coord) && !org.isDead()) {
                return true; // Found an Organism with the specified coordinates
            }
        }
        return false; // No Organism with the specified coordinates found
    }

    public void addOrganism(Organism org) {
        if (!(org instanceof Human)) { // Human does not have a species counter
            speciesCounter[org.getIndex()] += 1; // Increase the counter by 1
            org.setID(speciesCounter[org.getIndex()]); // Set the organism's ID to the counter value
        }
        organisms.add(org);
    }

    public abstract void drawWorld();
    
    public void prompt(String message) {
    	gameMenu.promptOutput(message + "\n");
    }

    public void doTurn() {
        turn++;
        gameMenu.clearTextArea();
        organisms.sort((a, b) -> {
            if (a.getInitiative() != b.getInitiative()) {
                return a.getInitiative() > b.getInitiative() ? -1 : 1;
            } else if (a.getAge() != b.getAge()) {
                return a.getAge() > b.getAge() ? -1 : 1;
            } else if (a.getSprite() != b.getSprite()) {
                return a.getSprite() > b.getSprite() ? -1 : 1;
            } else {
                return a.getID() < b.getID() ? -1 : 1;
            }
        });

        for (int i = 0; i < organisms.size(); i++) {
            if (organisms.get(i).getAge() > -1 && !organisms.get(i).isDead()) {
            	organisms.get(i).action();
            }
        }

        for (int i = organisms.size() - 1; i >= 0; i--) {
            if (organisms.get(i).isDead()) {
                organisms.remove(i);
            }
        }

        for (Organism org : organisms) {
            org.endTurn();
        }
        
        drawWorld();
    }

    public void clearBoard() {
        organisms.clear();
    }
    
    public abstract boolean checkBoundaries (Coordinate coord);

    public abstract void initializeBoard();
    
    public void readInputs(BufferedReader file) throws IOException {
        String line;
        while ((line = file.readLine()) != null) {
            if (!line.isEmpty()) {
                String[] parts = line.split(" ");
                char sprite = parts[0].charAt(0);
                int strength = Integer.parseInt(parts[1]);
                int age = Integer.parseInt(parts[2]);
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                Coordinate coord = new Coordinate(x, y);
                Species organismType = Species.fromSprite(sprite);
                switch (organismType) {
                    case HUMAN: {
                        int superStrengthTimer = Integer.parseInt(parts[5]);
                        Human h = new Human(this, coord, strength, age, superStrengthTimer);
                        this.human = h;
                        break;
                    }
                    case WOLF: {
                        Wolf w = new Wolf(this, coord, strength, age);
                        break;
                    }
                    case SHEEP: {
                        Sheep s = new Sheep(this, coord, strength, age);
                        break;
                    }
                    case FOX: {
                        Fox f = new Fox(this, coord, strength, age);
                        break;
                    }
                    case TURTLE: {
                        Turtle t = new Turtle(this, coord, strength, age);
                        break;
                    }
                    case ANTILOPE: {
                        Antilope a = new Antilope(this, coord, strength, age);
                        break;
                    }
                    case DANDELION: {
                        Dandelion d = new Dandelion(this, coord, strength, age);
                        break;
                    }
                    case GRASS: {
                        Grass g = new Grass(this, coord, strength, age);
                        break;
                    }
                    case GUARANA: {
                        Guarana u = new Guarana(this, coord, strength, age);
                        break;
                    }
                    case SOSNOWSKY: {
                        Sosnowsky b = new Sosnowsky(this, coord, strength, age);
                        break;
                    }
                    case NIGHTSHADE: {
                        Nightshade n = new Nightshade(this, coord, strength, age);
                        break;
                    }
                }
            }
        }
    }
    
    public abstract void saveState();
    
    public void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
    
    public int getTurn() {
        return turn;
    }
    
    public Human getHuman() {
        return human;
    }
    
    public void killHuman() {
        human = null;
    }
    
}
