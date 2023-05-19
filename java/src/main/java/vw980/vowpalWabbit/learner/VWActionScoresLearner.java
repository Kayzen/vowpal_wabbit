package vw980.vowpalWabbit.learner;

import vw980.vowpalWabbit.responses.ActionScores;

public final class VWActionScoresLearner extends VWLearnerBase<ActionScores> {
    VWActionScoresLearner(final long nativePointer) {
        super(nativePointer);
    }

    @Override
    protected native ActionScores predict(String example, boolean learn, long nativePointer);

    @Override
    protected native ActionScores predictMultiline(String[] example, boolean learn, long nativePointer);
}
