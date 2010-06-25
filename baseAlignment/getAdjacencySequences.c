/*
 * getSequences.c
 *
 *  Created on: 24 Jun 2010
 *      Author: benedictpaten
 */


/*
 * Gets the raw sequence.
 */
char *getAdjacencySequence(Cap *cap, int32_t maxLength) {
        Sequence *sequence = cap_getSequence(cap);
        assert(sequence != NULL);
        Cap *cap2 = cap_getAdjacency(cap);
        assert(!cap_getSide(cap));

        if(cap_getStrand(cap)) {
                int32_t length = cap_getCoordinate(cap2)
                                        - cap_getCoordinate(cap) - 1;
                assert(length >= 0);
                assert(maxLength >= 0);
                return sequence_getString(sequence, cap_getCoordinate(
                                        cap) + 1, length > maxLength ? maxLength : length, 1);
        }
        else {
                int32_t length = cap_getCoordinate(cap)
                                - cap_getCoordinate(cap2) - 1;
                assert(length >= 0);
                return sequence_getString(sequence,
                                length > maxLength ?
                                cap_getCoordinate(cap) - maxLength:
                                cap_getCoordinate(cap2) + 1,
                                length > maxLength ? maxLength : length, 0);
        }
}

/*
 * Datastructure to hold adjacency sequence.
 */
typedef struct _AdjacencySequence {
        char *string;
        char *sequenceName;
        int32_t strand;
        int32_t start;
        int32_t length;
} AdjacencySequence;

/*
 * Function to get an adjacency sequence.
 */
AdjacencySequence *getAdjacencySequenceAndCoordinates(Cap *cap, int32_t maxLength) {
        assert(!cap_getSide(cap));
        AdjacencySequence *subSequence = (AdjacencySequence *)st_malloc(sizeof(AdjacencySequence));
        subSequence->string = getAdjacencySequence(cap, maxLength);
        Sequence *sequence = cap_getSequence(cap);
        subSequence->sequenceName = netMisc_nameToString(sequence_getName(sequence));
        subSequence->strand = cap_getStrand(cap);
        subSequence->start = cap_getCoordinate(cap) + (cap_getStrand(cap) ? 1 : -1);
        subSequence->length = strlen(subSequence->string);
        return subSequence;
}

void destructAdjacencySequence(AdjacencySequence *subSequence) {
        free(subSequence->string);
        free(subSequence->sequenceName);
        free(subSequence);
}


