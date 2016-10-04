//
// Gabin Marignier - élève en 2e année à Télécom ParisTech - 2016
//

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.BorderLayout;

import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JToolBar;
import javax.swing.JMenuItem;
import javax.swing.JFrame;
import javax.swing.JPanel;

///
/// Fenêtre principale du programme contenant trois boutons : find media, play media et exit
///
public class Window extends JFrame {
	private static final long serialVersionUID = 1L;
	private JTextArea textArea;
	private JPanel panel;
	private JScrollPane scroll;
	private Client client;

	public Window (final Client client) {
		this.client = client;
		this.textArea = new JTextArea("",100,100);

		this.setTitle("Remote Controller");
		this.setResizable(true);
		this.setMinimumSize(new Dimension(500,200));
		this.setSize(500, 200);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLayout(new BorderLayout());
		this.setLocationRelativeTo(null);

		panel = new JPanel();
		panel.setLayout(new GridLayout(3,1));
		panel.setMaximumSize(new Dimension(100,100));

		panel.add(new TextButton("Find media",textArea,this.client));
		panel.add(new TextButton("Play media",textArea,this.client));
		panel.add(new ExitButton("Exit"));
		this.getContentPane().add(panel,BorderLayout.EAST);


		scroll = new JScrollPane(textArea);
		this.getContentPane().add(scroll,BorderLayout.CENTER);

		ActionListener action1 = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				try {
					String multiName = JOptionPane.showInputDialog("Which media are you looking for ?");
					String answer = client.send("find "+multiName);
					textArea.append(answer+'\n');
				}
				catch (Exception e) {
					textArea.append(e.getMessage());
					return;
				}
			}
		};

		ActionListener action2 = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				try {
					String multiName = JOptionPane.showInputDialog("Which media do you want to play ?");
					String answer = client.send("play "+multiName);
					textArea.append(answer+'\n');
				}
				catch (Exception e) {
					textArea.append(e.getMessage());
					return;
				}
			}
		};

		ActionListener action3 = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				System.exit(0);
			}
		};

		// Set JMenu
		JMenu menu = new JMenu("File");
		JMenuItem menuItem1 = new JMenuItem("Find media");
		JMenuItem menuItem2 = new JMenuItem("Play media");
		JMenuItem menuItem3 = new JMenuItem("Exit");
		menuItem1.addActionListener(action1);
		menuItem2.addActionListener(action2);
		menuItem3.addActionListener(action3);
		menu.add(menuItem1);
		menu.add(menuItem2);
		menu.add(menuItem3);
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(menu);
		this.setJMenuBar(menuBar);

		// Set ToolBar
		JToolBar toolBar = new JToolBar();
		JMenuItem toolItem1 = new JMenuItem("Find media");
		JMenuItem toolItem2 = new JMenuItem("Play media");
		JMenuItem toolItem3 = new JMenuItem("Exit");
		toolItem1.addActionListener(action1);
		toolItem2.addActionListener(action2);
		toolItem3.addActionListener(action3);
		toolBar.add(toolItem1);
		toolBar.add(toolItem2);
		toolBar.add(toolItem3);
		this.getContentPane().add(toolBar,BorderLayout.NORTH);

	    
		this.setVisible(true);
	}
}
