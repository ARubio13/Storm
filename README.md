#Storm
Manage storm event data indexed by a hash table, a binary search tree (BST), and max-heap as appropriate to support the queries.

##Storm and Fatality Event Data

###details-YYYY.csv
Each line of a file **details-YYYY.csv** contains details of a storm event described by the following 13 fields, in order. The only exception is the first line which contains the field names, and should be skipped.

1. **event_id:** An identifier assigned by the **NWS** for a specific storm event; it links the storm event with the information in the **fatalities-YYYY.csv** file. Example: 383097.
2. **state:** The state name, spelled in all capital letters, where the event occurred. Example: GEORGIA.
3. **year:** The four digit year for the event in this record. Example: 2000.
4. **month_name:** Name of the month for the event in this record spelled out. Example: January.
5. **event_type:** The event types permitted are listed in Table 1, spelled out.
6. **cz_type:** Indicates whether the event happened in a county/parish (C), zone (Z), or marine (M).
7. **cz_name:** County/Parish, Zone or Marine name assigned to the county or zone. Example: AIKEN.
8. **injuries_direct:** The number of injuries directly related to the weather event. Examples: 0, 56.
9. **injuries_indirect:** The number of injuries indirectly related to the weather event. Examples: 0, 87.
10. **deaths_direct:** The number of deaths directly related to the weather event. Examples: 0, 23.
11. **deaths_indirect:** The number of deaths indirectly related to the weather event. Examples: 0, 4, 6.
12. **damage_property:** The estimated amount of damage to property incurred by the weather event, e.g.,
10.00K = $10,000; 10.00M = $10,000,000. Examples: 10.00K, 0.00K, 10.00M.
13. **damage_crops:** The estimated amount of damage to crops incurred by the weather event e.g., 10.00K = $10,000; 10.00M = $10,000,000. Examples: 0.00K, 500.00K, 15.00M.

###fatalities-YYYY.csv
Each line of a **fatalities-YYYY.csv** file contains information on fatalities associated with a storm event, described by the following 7 fields, in order. Similar to a **details-YYYY.csv** file, the first line does not contain data and should be skipped.

1. **fatality_id:** An identifier assigned by NWS to denote the individual fatality that occurred within a storm event. Example: 17582.
2. **event_id:** An identifier assigned by NWS to denote a specific storm event; it links the fatality with the storm event in the **details-YYYY.csv** file. Example: 383097.
3. **fatality_type:** D represents a direct fatality, whereas I represents an indirect fatality. Example: D.
4. **fatality_date:** Date and time of fatality in MM/DD/YYYY HH:MM:SS format, 24 hour time.
Example: 04/03/2012 12:00:00.
5. **fatality_age:** The age of the person suffering the fatality. Example: 38.
6. **fatality_sex:** The gender of the person suffering the fatality. Example: F.
7. **fatality_location:** The fatality locations permitted are listed in Table 2, spelled out. Example: UT is Under Tree.

##Requirements for Milestone Deadline
For the milestone deadline, the only query you need to support is the **range**, i.e., the hash table and heap need not be constructed yet. Constructing a BST to answer each **range** query as described in **checklist-Milestone.txt**. In addition, print the characteristics of the BST as described in §3.
Submission instructions for the milestone as well as a grading rubric will be posted on Canvas. Sample input will be provided on Canvas.
The milestone is worth 30% of the total project grade.
