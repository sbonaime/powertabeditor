/*
  * Copyright (C) 2011 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <catch.hpp>

#include <boost/make_shared.hpp>
#include <powertabdocument/direction.h>
#include <powertabdocument/barline.h>
#include <powertabdocument/staff.h>
#include <powertabdocument/system.h>

TEST_CASE("PowerTabDocument/System/FindStaffIndex/NoStaves", "")
{
    System emptySystem;
    boost::shared_ptr<Staff> staff;

    REQUIRE_THROWS_AS(emptySystem.FindStaffIndex(staff), std::out_of_range);
}

TEST_CASE("PowerTabDocument/System/CopyAndEquality", "")
{
    System system1;
    system1.InsertBarline(System::BarlinePtr(new Barline(2, Barline::doubleBar, 0)));
    System system2 = system1;

    REQUIRE(system1 == system2);

    // check deep copy
    system1.GetBarlineAtPosition(2)->SetBarlineData(Barline::repeatStart, 0);
    REQUIRE(system1 != system2);
}

TEST_CASE("PowerTabDocument/System/Directions", "")
{
    System system;
    REQUIRE(system.GetDirectionCount() == 0);

    boost::shared_ptr<Direction> dir1 = boost::make_shared<Direction>(5,
            Direction::dalSegno, Direction::activeNone, 0);
    boost::shared_ptr<Direction> dir2 = boost::make_shared<Direction>(2,
            Direction::daCapo, Direction::activeNone, 0);

    system.InsertDirection(dir1);
    system.InsertDirection(dir2);
    REQUIRE(system.GetDirectionCount() == 2);
    REQUIRE(system.GetDirection(0) == dir2); // Should be ordered by position.

    REQUIRE(system.FindDirection(5));
    REQUIRE(system.FindDirection(2));
    REQUIRE(!system.FindDirection(0));
    REQUIRE(!system.FindDirection(7));

    system.RemoveDirection(dir2);
    REQUIRE(system.GetDirectionCount() == 1);
}
