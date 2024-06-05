package worldsimulator;

import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import javax.swing.*;

public class GameMenu implements ActionListener{

	private JFrame frame;
	private JLabel turnLabel;
	private JTextArea promptTextArea;
	private JScrollPane scrollPane;
	private JPanel buttonPanel;
	private JPanel boardPanel;
	private JButton[][] boardButtons;
	private HashMap<JButton, Coordinate> buttonCoordinates;
	
	public void showMainMenu() {
        JFrame frame = new JFrame("World Simulator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);
        frame.setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 1, 10, 10));

        JButton newGameButton = new JButton("New Game");
        JButton loadGameButton = new JButton("Load Game");
        JButton exitButton = new JButton("Exit");

        newGameButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                World world = new GridWorld();
                setupNewGame(world);
            }
        });

        loadGameButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                World world = new GridWorld();
                loadState(world);
            }
        });

        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        panel.add(newGameButton);
        panel.add(loadGameButton);
        panel.add(exitButton);

        frame.add(panel);
        frame.setVisible(true);
    }
	
	public void setupNewGame(World world) {
		// Prompt for board type
        String[] boardTypes = {"Grid", "Hex"};
        String boardType = (String) JOptionPane.showInputDialog(
                null,
                "Select board type:",
                "World Simulator",
                JOptionPane.QUESTION_MESSAGE,
                null,
                boardTypes,
                boardTypes[0]
        );

        if (boardType == null) {
            System.exit(0); // Exit if user cancels
        }

        // Prompt for board size
        if (boardType.equals("Grid")) {
        	JTextField rowsField = new JTextField(5);
            JTextField columnsField = new JTextField(5);

            JPanel panel = new JPanel();
            panel.add(new JLabel("Rows:"));
            panel.add(rowsField);
            panel.add(Box.createHorizontalStrut(15)); // a spacer
            panel.add(new JLabel("Columns:"));
            panel.add(columnsField);

            int result = JOptionPane.showConfirmDialog(null, panel,
                    "Enter Board Size", JOptionPane.OK_CANCEL_OPTION);
            int rows = 0;
            int columns = 0;
            if (result == JOptionPane.OK_OPTION) {
                try {
                    rows = Integer.parseInt(rowsField.getText());
                    columns = Integer.parseInt(columnsField.getText());
                    if (rows > Constants.GRID_WORLD_MAX_HEIGHT || columns > Constants.GRID_WORLD_MAX_HEIGHT ||
                    	rows < Constants.GRID_WORLD_MIN_HEIGHT || columns < Constants.GRID_WORLD_MIN_HEIGHT) {
                    	JOptionPane.showMessageDialog(null, ("Invalid input. Proper dimensions " + Constants.GRID_WORLD_MIN_HEIGHT + " ÷ " + Constants.GRID_WORLD_MAX_HEIGHT + "."), "Error", JOptionPane.ERROR_MESSAGE);
                        System.exit(0); // Exit if invalid input
                    }
                    world = new GridWorld(rows, columns);
            		world.initializeBoard();
            		initializeGridGUI((GridWorld) world);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Invalid input. Please enter valid integers for rows and columns.", "Error", JOptionPane.ERROR_MESSAGE);
                    System.exit(0); // Exit if invalid input
                }
            } else {
                System.exit(0); // Exit if user cancels
            }
        } else if (boardType.equals("Hex")) {
        	JTextField sizeField = new JTextField(5);

            JPanel panel = new JPanel();
            panel.add(new JLabel("Size:"));
            panel.add(sizeField);
            
            int result = JOptionPane.showConfirmDialog(null, panel,
                    "Enter Board Size", JOptionPane.OK_CANCEL_OPTION);
            int size = 0;
            if (result == JOptionPane.OK_OPTION) {
                try {
                    size = Integer.parseInt(sizeField.getText());
                    if (size > Constants.HEX_WORLD_MAX_SIZE || size < Constants.HEX_WORLD_MIN_SIZE) {
                        	JOptionPane.showMessageDialog(null, ("Invalid input. Proper dimensions " + Constants.HEX_WORLD_MIN_SIZE + " ÷ " + Constants.HEX_WORLD_MAX_SIZE + "."), "Error", JOptionPane.ERROR_MESSAGE);
                            System.exit(0); // Exit if invalid input
                        }
                    world = new HexWorld(size);
            		world.initializeBoard();
            		initializeHexGUI((HexWorld) world);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Invalid input. Please enter valid integers for rows and columns.", "Error", JOptionPane.ERROR_MESSAGE);
                    System.exit(0); // Exit if invalid input
                }
            } else {
                System.exit(0); // Exit if user cancels
            }
        }
	}
	
    public void initializeGridGUI(GridWorld world) {
    	world.setGameMenu(this);
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	boardButtons = new JButton[world.getRows()][world.getColumns()];
            	buttonCoordinates = new HashMap<>();
            	
                frame = new JFrame("Custom Swing GUI");
                frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                frame.setSize(1200, 800);
                frame.setTitle("World Simulator - Michał Kwitek 186531");
                frame.setLocationRelativeTo(null);
                
                // NORTH: Turn
                turnLabel = new JLabel(("TURN " + world.getTurn()), SwingConstants.CENTER);
                turnLabel.setFont(new Font("Serif", Font.BOLD, 24));
                frame.add(turnLabel, BorderLayout.NORTH);
                
                // SOUTH: Text area for prompting messages
                promptTextArea = new JTextArea(10, 20);
                promptTextArea.setLineWrap(true);
                promptTextArea.setWrapStyleWord(true);
                scrollPane = new JScrollPane(promptTextArea);
                frame.add(scrollPane, BorderLayout.SOUTH);
                
                // WEST: Space for action buttons
                buttonPanel = new JPanel() ;
                
                buttonPanel.setLayout(new GridLayout(6, 1));
                JButton nextTurnButton = new JButton("NEXT TURN");
                JButton upButton = new JButton("UP");
                JButton leftButton = new JButton("LEFT");
                JButton rightButton = new JButton("RIGHT");
                JButton downButton = new JButton("DOWN");
                JButton superPowerButton = new JButton("SUPER POWER");
                JButton saveButton = new JButton("SAVE");
                JButton loadButton = new JButton("LOAD");
                JButton returnButton = new JButton("MENU");

                nextTurnButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                    		if (world.getHuman().getMoveDirection() != null) {
                    			if(world.getHuman().canHumanMove()) {
                            		world.doTurn();
                            	}
                            	else {
                            		promptTextArea.append("human nie moze sie ruszyc w wybranym kierunku\n");
                            	}
                    		} else {
                    			promptTextArea.append("wybierz kierunek ruchu dla human\n");
                    		}
                    	} else {
                    		world.doTurn();
                    	}
                    }
                });

                superPowerButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if (world.getHuman() != null) {
                    		world.getHuman().activateSuperStrength();
                    	}
                    }
                });

                saveButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        world.saveState();
                    }
                });
                
                loadButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	loadState(world);
                    }
                });
                
                returnButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	world.clearBoard();
                    	if (frame != null) {
                    		frame.dispose();
                    	}
                    	showMainMenu();
                    }
                });

                buttonPanel.add(nextTurnButton);
                      
                JPanel movementPanel = new JPanel();
                movementPanel.setLayout(new GridLayout(3, 3));
                movementPanel.add(new JLabel());
                movementPanel.add(upButton);
                movementPanel.add(new JLabel());
                movementPanel.add(leftButton);
                movementPanel.add(new JLabel());
                movementPanel.add(rightButton);
                movementPanel.add(new JLabel());
                movementPanel.add(downButton);
                movementPanel.add(new JLabel());
                
                upButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.NORTH);
                        	promptTextArea.append("human ruszy się NORTH\n");
                    	}
                    }
                });

                leftButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.WEST);
                        	promptTextArea.append("human ruszy się WEST\n");
                    	}
                    }
                });
                
                rightButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.EAST);
                        	promptTextArea.append("human ruszy się EAST\n");
                    	}
                    }
                });
                
                downButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.SOUTH);
                        	promptTextArea.append("human ruszy się SOUTH\n");
                    	}
                    }
                });
                
                buttonPanel.add(movementPanel);
                
                buttonPanel.add(superPowerButton);
                buttonPanel.add(saveButton);
                buttonPanel.add(loadButton);
                buttonPanel.add(returnButton);

                frame.add(buttonPanel, BorderLayout.WEST);

                // CENTER: Board of rectangular buttons
                boardPanel = new JPanel();
                boardPanel.setLayout(new GridLayout(world.getRows(), world.getColumns(), 0, 0));

                for (int row = 0; row < world.getRows(); row++) {
                    for (int col = 0; col < world.getColumns(); col++) {
                        Coordinate coord = new Coordinate(col, row);
                        Organism org = world.findOrganismByCoordinate(coord);
                        String sprite = "\u200B";
                        if (org != null) {
                            sprite = sprite.replace('\u200B', org.getSprite());
                        }
                        JButton boardButton = new JButton(sprite);
                        
                        boardButton.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                            	JButton clickedButton = (JButton) e.getSource();
                            	Coordinate spawnCoord = buttonCoordinates.get(clickedButton);
                            	Organism newOrganism = world.findOrganismByCoordinate(spawnCoord);
                            	if(newOrganism == null) {
                                    // Options to choose from
                                    String[] options = {
                                        Species.WOLF.getName(), Species.SHEEP.getName(), Species.ANTILOPE.getName(), Species.TURTLE.getName(), 
                                        Species.FOX.getName(), Species.GRASS.getName(), Species.DANDELION.getName(), Species.GUARANA.getName(), 
                                        Species.NIGHTSHADE.getName(), Species.SOSNOWSKY.getName()
                                    };

                                    // Show the option dialog
                                    String selectedOption = (String) JOptionPane.showInputDialog(
                                            frame,
                                            "Wybierz organizm:",
                                            "Wybór organizmu",
                                            JOptionPane.PLAIN_MESSAGE,
                                            null,
                                            options,
                                            options[0]
                                    );

                                    // Handle the selected option
                                    if (selectedOption != null) {
                                    	Species organismType = Species.fromName(selectedOption);
                                    	switch (organismType) {
                                        case WOLF:
                                            newOrganism = new Wolf(world, spawnCoord);
                                            break;
                                        case SHEEP:
                                            newOrganism = new Sheep(world, spawnCoord);
                                            break;
                                        case ANTILOPE:
                                            newOrganism = new Antilope(world, spawnCoord);
                                            break;
                                        case TURTLE:
                                            newOrganism = new Turtle(world, spawnCoord);
                                            break;
                                        case FOX:
                                            newOrganism = new Fox(world, spawnCoord);
                                            break;
                                        case GRASS:
                                            newOrganism = new Grass(world, spawnCoord);
                                            break;
                                        case DANDELION:
                                            newOrganism = new Dandelion(world, spawnCoord);
                                            break;
                                        case GUARANA:
                                            newOrganism = new Guarana(world, spawnCoord);
                                            break;
                                        case NIGHTSHADE:
                                            newOrganism = new Nightshade(world, spawnCoord);
                                            break;
                                        case SOSNOWSKY:
                                            newOrganism = new Sosnowsky(world, spawnCoord);
                                            break;
                                    	}
                                    	clickedButton.setText(String.valueOf(newOrganism.getSprite()));
                                    }
                            	}
                            }
                        });

                        boardButtons[row][col] = boardButton; // Store button reference
                        buttonCoordinates.put(boardButton, coord);
                        boardPanel.add(boardButton);
                    }
                }

                frame.add(boardPanel, BorderLayout.CENTER);
                
                // Display the window.
                
                frame.setVisible(true);
            }
        });
    	
    	    }

    public void initializeHexGUI(HexWorld world) {
    	world.setGameMenu(this);
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	boardButtons = new JButton[world.getSize()][world.getSize()];
            	buttonCoordinates = new HashMap<>();
            	
                frame = new JFrame("Custom Swing GUI");
                frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                frame.setSize(1200, 800);
                frame.setTitle("World Simulator - Michał Kwitek 186531");
                frame.setLocationRelativeTo(null);
                
                // NORTH: Turn
                turnLabel = new JLabel(("TURN " + world.getTurn()), SwingConstants.CENTER);
                turnLabel.setFont(new Font("Serif", Font.BOLD, 24));
                frame.add(turnLabel, BorderLayout.NORTH);
                
                // SOUTH: Text area for prompting messages
                promptTextArea = new JTextArea(10, 20);
                promptTextArea.setLineWrap(true);
                promptTextArea.setWrapStyleWord(true);
                scrollPane = new JScrollPane(promptTextArea);
                frame.add(scrollPane, BorderLayout.SOUTH);
                
                // WEST: Space for action buttons
                buttonPanel = new JPanel();
                
                buttonPanel.setLayout(new GridLayout(6, 1));
                JButton nextTurnButton = new JButton("NEXT TURN");
                JButton upButton = new JButton("UP");
                JButton upLeftButton = new JButton("UP-LEFT");
                JButton upRightButton = new JButton("UP-RIGHT");
                JButton downLeftButton = new JButton("DOWN-LEFT");
                JButton downRightButton = new JButton("DOWN-RIGHT");
                JButton downButton = new JButton("DOWN");
                JButton superPowerButton = new JButton("SUPER POWER");
                JButton saveButton = new JButton("SAVE");
                JButton loadButton = new JButton("LOAD");
                JButton returnButton = new JButton("MENU");

                nextTurnButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                    		if (world.getHuman().getMoveDirection() != null) {
                    			if(world.getHuman().canHumanMove()) {
                            		world.doTurn();
                            	}
                            	else {
                            		promptTextArea.append("human nie moze sie ruszyc w wybranym kierunku\n");
                            	}
                    		} else {
                    			promptTextArea.append("wybierz kierunek ruchu dla human\n");
                    		}
                    	} else {
                    		world.doTurn();
                    	}
                    }
                });

                superPowerButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if (world.getHuman() != null) {
                    		world.getHuman().activateSuperStrength();
                    	}
                    }
                });

                saveButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        world.saveState();
                    }
                });
                
                loadButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	loadState(world);
                    }
                });
                
                returnButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	world.clearBoard();
                    	if (frame != null) {
                    		frame.dispose();
                    	}
                    	showMainMenu();
                    }
                });

                buttonPanel.add(nextTurnButton);
                      
                JPanel movementPanel = new JPanel();
                movementPanel.setLayout(new GridLayout(2, 3));
                movementPanel.add(upLeftButton);
                movementPanel.add(upButton);
                movementPanel.add(upRightButton);
                movementPanel.add(downLeftButton);
                movementPanel.add(downButton);
                movementPanel.add(downRightButton);
                
                upButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.NORTH);
                        	promptTextArea.append("human ruszy się NORTH\n");
                    	}
                    }
                });

                upLeftButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.NORTH_WEST);
                        	promptTextArea.append("human ruszy się NORTH-WEST\n");
                    	}
                    }
                });
                
                upRightButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.NORTH_EAST);
                        	promptTextArea.append("human ruszy się NORTH-EAST\n");
                    	}
                    }
                });
                
                downLeftButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.SOUTH_WEST);
                        	promptTextArea.append("human ruszy się SOUTH-WEST\n");
                    	}
                    }
                });
                
                downRightButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.SOUTH_EAST);
                        	promptTextArea.append("human ruszy się SOUTH-EAST\n");
                    	}
                    }
                });
                
                downButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	if(world.getHuman() != null) {
                        	world.getHuman().setMoveDirection(Directions.SOUTH);
                        	promptTextArea.append("human ruszy się SOUTH\n");
                    	}
                    }
                });
                
                buttonPanel.add(movementPanel); 
                buttonPanel.add(superPowerButton);
                buttonPanel.add(saveButton);
                buttonPanel.add(loadButton);
                buttonPanel.add(returnButton);

                frame.add(buttonPanel, BorderLayout.WEST);

                // CENTER: Board of rectangular buttons
                boardPanel = new JPanel();
                boardPanel.setLayout(new BoxLayout(boardPanel, BoxLayout.X_AXIS));
                boardPanel.add(Box.createHorizontalGlue());
                int columnPanelSize = 1;
                for (int j = 0; j < world.getSize(); j++) {
                	JPanel columnPanel = new JPanel();
                	columnPanel.setLayout(new BoxLayout(columnPanel, BoxLayout.Y_AXIS));
                	columnPanel.add(Box.createVerticalGlue());
                	int row = world.getSize() - 1 - j;
                	int col = world.getSize() - 1;
                    for (int i = 0; i < columnPanelSize; i++) {
                    	JButton boardButton = createBoardButton(world, row, col);
                    	//JButton boardButton = new JButton(row + "," + col);
                        columnPanel.add(boardButton);
                        boardButtons[row][col] = boardButton; // Store button reference
                        Coordinate coord = new Coordinate(row, col);
                        buttonCoordinates.put(boardButton, coord);
                        row++;
                        col--;
                    }
                    columnPanel.add(Box.createVerticalGlue());
                    boardPanel.add(columnPanel);
                    columnPanelSize++;
                }
                columnPanelSize = world.getSize() - 1;
                for (int j = 0; j < world.getSize() - 1; j++) {
                	JPanel columnPanel = new JPanel();
                	columnPanel.setLayout(new BoxLayout(columnPanel, BoxLayout.Y_AXIS));
                	columnPanel.add(Box.createVerticalGlue());
                	int row = 0;
                	int col = world.getSize() - 2 - j;
                    for (int i = 0; i < columnPanelSize; i++) {
                    	JButton boardButton = createBoardButton(world, row, col);
                    	//JButton boardButton = new JButton(row + "," + col);
                        columnPanel.add(boardButton);
                        boardButtons[row][col] = boardButton; // Store button reference
                        Coordinate coord = new Coordinate(row, col);
                        buttonCoordinates.put(boardButton, coord);
                        row++;
                        col--;
                    }
                    columnPanel.add(Box.createVerticalGlue());
                    boardPanel.add(columnPanel);
                    columnPanelSize--;
                }
                boardPanel.add(Box.createHorizontalGlue());
                frame.add(boardPanel, BorderLayout.CENTER);
                
                // Display the window.
                
                frame.setVisible(true);
            }
        });
    	
    	    }
    
    public void clearTextArea() {
        promptTextArea.setText("");
    }
	
    public void updateGridBoardButtons(GridWorld world) {
    	turnLabel.setText(String.valueOf("TURN " + world.getTurn()));
        for (int row = 0; row < world.getRows(); row++) {
            for (int col = 0; col < world.getColumns(); col++) {
                Coordinate coord = new Coordinate(col, row);
                Organism org = world.findOrganismByCoordinate(coord);
                String sprite = "\u200B";
                if (org != null) {
                    sprite = sprite.replace('\u200B', org.getSprite());
                }
                boardButtons[row][col].setText(sprite); // Update button text
            }
        }
    }
    
    public void updateHexBoardButtons(HexWorld world) {
    	turnLabel.setText(String.valueOf("TURN " + world.getTurn()));
        for (int row = 0; row < world.getSize(); row++) {
            for (int col = 0; col < world.getSize(); col++) {
                Coordinate coord = new Coordinate(row, col);
                Organism org = world.findOrganismByCoordinate(coord);
                String sprite = "\u200B";
                if (org != null) {
                    sprite = sprite.replace('\u200B', org.getSprite());
                }
                boardButtons[row][col].setText(sprite); // Update button text
            }
        }
    }
    
    public void promptOutput(String message) {
    	SwingUtilities.invokeLater(new Runnable() {
    		public void run() {
                // Update Swing components with the result
                promptTextArea.append(message);
            }
        });
    }
    
    public void loadState(World world) {
        boolean opened = false;
        while (!opened) {
            // Prompt user for file name using GUI
            JFileChooser fileChooser = new JFileChooser();
            int result = fileChooser.showOpenDialog(null);
            if (result == JFileChooser.APPROVE_OPTION) {
                File selectedFile = fileChooser.getSelectedFile();
                try (BufferedReader file = new BufferedReader(new FileReader(selectedFile))) {
                    world.clearBoard();
                    String worldType = file.readLine();
                    if (worldType.equals("Grid")) {
                    	String[] dimensions = file.readLine().split(" ");
                        int rows = Integer.parseInt(dimensions[0]);
                        int columns = Integer.parseInt(dimensions[1]);
                        world.clearBoard();
                        world = new GridWorld(rows, columns);
                    } else if (worldType.equals("Hex")) {
                    	String dimensions = file.readLine();
                        int size = Integer.parseInt(dimensions);
                        world.clearBoard();
                        world = new HexWorld(size);
                    } else {
                        JOptionPane.showMessageDialog(null, "File corrupted.", "Error", JOptionPane.ERROR_MESSAGE);
                        break;  // Exit the loop if no file is selected
                    }
                    world.readInputs(file);
                    if (world instanceof GridWorld) {
                    	if (frame != null) {
                    		frame.dispose();
                    	}
                    	initializeGridGUI((GridWorld) world);
                    } else if (world instanceof HexWorld) {
                    	if (frame != null) {
                    		frame.dispose();
                    	}
                    	initializeHexGUI((HexWorld) world);
                    }
                    opened = true;
                } catch (FileNotFoundException e) {
                    JOptionPane.showMessageDialog(null, "File not found.", "Error", JOptionPane.ERROR_MESSAGE);
                } catch (IOException e) {
                    JOptionPane.showMessageDialog(null, "An error occurred while reading the file.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(null, "No file selected.", "Error", JOptionPane.ERROR_MESSAGE);
                break;  // Exit the loop if no file is selected
            }
        }
    }

	private JButton createBoardButton(World world, int row, int col) {
		
		Coordinate coord = new Coordinate(row, col);
        Organism org = world.findOrganismByCoordinate(coord);
        String sprite = "\u200B";
        if (org != null) {
            sprite = sprite.replace('\u200B', org.getSprite());
        }
        
        JButton boardButton = new JButton(sprite);
        Dimension size = new Dimension(50, 50); // Example button size
        boardButton.setPreferredSize(size);
        boardButton.setMinimumSize(size);
        boardButton.setMaximumSize(size);
        
        boardButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	JButton clickedButton = (JButton) e.getSource();
            	Coordinate spawnCoord = buttonCoordinates.get(clickedButton);
            	Organism newOrganism = world.findOrganismByCoordinate(spawnCoord);
            	if(newOrganism == null) {
                    // Options to choose from
                    String[] options = {
                        Species.WOLF.getName(), Species.SHEEP.getName(), Species.ANTILOPE.getName(), Species.TURTLE.getName(), 
                        Species.FOX.getName(), Species.GRASS.getName(), Species.DANDELION.getName(), Species.GUARANA.getName(), 
                        Species.NIGHTSHADE.getName(), Species.SOSNOWSKY.getName()
                    };

                    // Show the option dialog
                    String selectedOption = (String) JOptionPane.showInputDialog(
                            frame,
                            "Wybierz organizm:",
                            "Wybór organizmu",
                            JOptionPane.PLAIN_MESSAGE,
                            null,
                            options,
                            options[0]
                    );

                    // Handle the selected option
                    if (selectedOption != null) {
                    	Species organismType = Species.fromName(selectedOption);
                    	switch (organismType) {
                        case WOLF:
                            newOrganism = new Wolf(world, spawnCoord);
                            break;
                        case SHEEP:
                            newOrganism = new Sheep(world, spawnCoord);
                            break;
                        case ANTILOPE:
                            newOrganism = new Antilope(world, spawnCoord);
                            break;
                        case TURTLE:
                            newOrganism = new Turtle(world, spawnCoord);
                            break;
                        case FOX:
                            newOrganism = new Fox(world, spawnCoord);
                            break;
                        case GRASS:
                            newOrganism = new Grass(world, spawnCoord);
                            break;
                        case DANDELION:
                            newOrganism = new Dandelion(world, spawnCoord);
                            break;
                        case GUARANA:
                            newOrganism = new Guarana(world, spawnCoord);
                            break;
                        case NIGHTSHADE:
                            newOrganism = new Nightshade(world, spawnCoord);
                            break;
                        case SOSNOWSKY:
                            newOrganism = new Sosnowsky(world, spawnCoord);
                            break;
                    	}
                    	clickedButton.setText(String.valueOf(newOrganism.getSprite()));
                    }
            	}
            }
        });

		return boardButton;
	}

	public void show() {
		this.frame.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
}