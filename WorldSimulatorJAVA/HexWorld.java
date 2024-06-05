package worldsimulator;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.swing.JOptionPane;

public class HexWorld extends World {

	private int size;
    private static final int[] xdirection = {-1, 0, -1, 0, 1, 1};
    private static final int[] ydirection = {1, -1, 0, 1, 0, -1};
    
	public HexWorld() {
        super();
        size = Constants.HEX_WORLD_DEFAULT_SIZE;
    }
	
	public HexWorld(int size) {
		super();
		this.size = size;
    }
	
	@Override
    public List<Coordinate> getAdjacentTiles (Coordinate coord) {
    	List<Coordinate> coordinates = new ArrayList<>();
    	for (int i = 0; i < xdirection.length; i++)
    	{
    		Coordinate adjacent = new Coordinate (HexWorld.xdirection[i] + coord.x, HexWorld.ydirection[i] + coord.y);
    		if (adjacent.x >= 0 && adjacent.y >= 0 && adjacent.x < getSize() && adjacent.y < getSize()) {
        		coordinates.add(adjacent);
        	}
    	}
    	return coordinates;
    }
	
	@Override
	public boolean checkBoundaries (Coordinate coord) {
		if (coord.x < 0 || coord.y < 0 || coord.x >= getSize() || coord.y >= getSize()) {
			return false;
		}
		return true;
	}
	
	@Override
    public void initializeBoard() {
        List<Coordinate> coords = new ArrayList<>();
        int organismNumber = new Random().nextInt((getSize() * getSize()) / 5);
        while (coords.size() <= organismNumber) {
            Coordinate coord = new Coordinate(new Random().nextInt(getSize()), new Random().nextInt(getSize()));
            if (!coords.contains(coord)) {
                coords.add(coord);
            }
        }
        for (int i = 0; i < coords.size() - 1; i++) {
            int typeRoll = new Random().nextInt(Constants.SPECIES_NUMBER);
            Species organismType = Species.fromOrdinal(typeRoll);
            Organism newOrganism = null;
            switch (organismType) {
                case WOLF:
                    newOrganism = new Wolf(this, coords.get(i));
                    break;
                case SHEEP:
                    newOrganism = new Sheep(this, coords.get(i));
                    break;
                case ANTILOPE:
                    newOrganism = new Antilope(this, coords.get(i));
                    break;
                case TURTLE:
                    newOrganism = new Turtle(this, coords.get(i));
                    break;
                case FOX:
                    newOrganism = new Fox(this, coords.get(i));
                    break;
                case GRASS:
                    newOrganism = new Grass(this, coords.get(i));
                    break;
                case DANDELION:
                    newOrganism = new Dandelion(this, coords.get(i));
                    break;
                case GUARANA:
                    newOrganism = new Guarana(this, coords.get(i));
                    break;
                case NIGHTSHADE:
                    newOrganism = new Nightshade(this, coords.get(i));
                    break;
                case SOSNOWSKY:
                    newOrganism = new Sosnowsky(this, coords.get(i));
                    break;
            }
        }
        Human h = new Human(this, coords.get(coords.size() - 1));
        this.human = h;
    }
	
	@Override
	public void saveState() {
        // Prompt user for file name
        String fileName = JOptionPane.showInputDialog(null, "Enter the file name to save the game state:");

        if (fileName != null && !fileName.trim().isEmpty()) {
            try (FileWriter file = new FileWriter(fileName)) {
            	file.write("Hex\n");
                file.write(size + "\n");
                for (Organism org : organisms) {
                    if (!org.isDead()) {
                        file.write(org.getSprite() + " " + org.getStrength() + " " + org.getAge() + " " + org.getXCoord() + " " + org.getYCoord());
                        if (org instanceof Human) {
                            Human h = (Human) org;
                            file.write(" " + h.getSuperStrengthTimer());
                        }
                        file.write("\n");
                    }
                }
                JOptionPane.showMessageDialog(null, "Game state saved successfully!");
            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, "An error occurred while saving the game state.", "Error", JOptionPane.ERROR_MESSAGE);
                e.printStackTrace();
            }
        } else {
            JOptionPane.showMessageDialog(null, "File name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

	public void drawWorld() {
    	gameMenu.updateHexBoardButtons(this);
    }
	
	public int getSize() {
		return size;
	}
	
}
