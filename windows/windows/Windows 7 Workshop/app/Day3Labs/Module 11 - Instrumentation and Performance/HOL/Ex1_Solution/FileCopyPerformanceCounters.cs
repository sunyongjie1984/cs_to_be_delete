using System.Diagnostics;

namespace Ex1_Starter
{
    static class FileCopyPerformanceCounters
    {
        public static void Initialize()
        {
            CounterCreationDataCollection counters = new CounterCreationDataCollection();
            CounterCreationData counter = new CounterCreationData(
                "Total Files Copied", "Total number of files copied by the application.",
                PerformanceCounterType.NumberOfItems32);
            counters.Add(counter);
            counter = new CounterCreationData(
                "% Files Copied", "Percent of files copied in the current operation.",
                PerformanceCounterType.NumberOfItems32);
            counters.Add(counter);

            if (PerformanceCounterCategory.Exists("FileCopier"))
                PerformanceCounterCategory.Delete("FileCopier");

            PerformanceCounterCategory.Create("FileCopier",
                "Instrumentation of the FileCopier application.",
                PerformanceCounterCategoryType.SingleInstance,
                counters);

            _totalFilesCounter = new PerformanceCounter(
                "FileCopier", "Total Files Copied", false);
            _percentDoneCounter = new PerformanceCounter(
                "FileCopier", "% Files Copied", false);
        }

        private static PerformanceCounter _totalFilesCounter;
        private static PerformanceCounter _percentDoneCounter;

        public static void UpdateTotalFiles(int totalFiles)
        {
            _totalFilesCounter.RawValue = totalFiles;
        }
        public static void UpdatePercentDone(int percentDone)
        {
            _percentDoneCounter.RawValue = percentDone;
        }
    }
}
