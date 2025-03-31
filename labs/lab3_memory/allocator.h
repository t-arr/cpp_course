/**
 * @file allocator.h
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 * @modified in Spring 2025 by Anna LaValle
 */

#ifndef ALLOCATOR_H
#define ALLOCATOR_H


/**
 * An allocator object to wrap the allocation of last-name letter groups
 * to rooms.
 */
class Allocator
{
	public:

        /**
         * Creates an Allocator object based on a list of students and a
         *  list of rooms.
         * @param studentFile Path to roster file
         * @param roomFile Path to room list file
         */
        Allocator(const std::string & studentFile, const std::string & roomFile);

        ~Allocator();
  
        /**
         * Calls the solving routine to allocate student letter
         *  groups to rooms.
         */
        void allocate();

        /**
         * Prints each letter and how many students there are for each one.
         */
        void printStudents();

        /**
         * Prints the room allocation determined by this Allocator.
         */
        void printRooms();

	private:

        /**
         * Creates the vector of letters.
         */
        void createLetterGroups();

        /**
         * Reads the students from the students file and places them in
         *  their letter groups.
         * @param file The file to read the student list from
         */
        void loadStudents(const std::string & file);

        /**
         * Reads rooms from the rooms file and sets their capacities.
         * @param file The file to read the room list from
         */
        void loadRooms(const std::string & file);

        /**
         * Runs the algorithm on the set of rooms and students.
         */
        int  solve();

        /**
         * Return the room with the largest number of open seasts
         */
        Room& largestOpening();

        /**
         * Returns the amount of seats remaining in the room with the
         *  fewest spare seats.
         */
        int minSpaceRemaining();

        /** Vector of all letters (size 26) */
        std::vector<Letter> alphabet;

        /** Vector of all rooms */
        std::vector<Room> rooms;

        /** Size of the rooms vector */
        int roomCount = 0;

        /** Total number of students */
        int studentCount = 0;

        /** Total number of available seats across all rooms */
        int totalCapacity = 0;
};

#endif
